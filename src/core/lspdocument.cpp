#include "lspdocument.h"
#include "lspdocument_p.h"

#include "json_utils.h"
#include "logger.h"
#include "string_utils.h"

#include "lsp/client.h"
#include "lsp/types.h"

#include "project.h"
#include "querymatch.h"
#include "rangemark.h"
#include "symbol.h"
#include "textlocation.h"

#include "scriptmanager.h"

#include <treesitter/languages.h>
#include <treesitter/parser.h>
#include <treesitter/predicates.h>
#include <treesitter/query.h>
#include <treesitter/tree.h>

#include <QFile>
#include <QJSEngine>
#include <QMap>
#include <QPlainTextEdit>
#include <QTextBlock>
#include <QTextDocument>
#include <QTextStream>

#include <kdalgorithms.h>
#include <spdlog/spdlog.h>

#include <algorithm>
#include <memory>

namespace Core {

/*!
 * \qmltype LspDocument
 * \brief Base document object for document using LSP.
 * \instantiates Core::LspDocument
 * \inqmlmodule Script
 * \since 4.0
 * \inherits TextDocument
 */

LspDocument::~LspDocument() = default;

LspDocument::LspDocument(Type type, QObject *parent)
    : TextDocument(type, parent)
    , m_cache(std::make_unique<LspCache>(this))
{
    connect(textEdit()->document(), &QTextDocument::contentsChange, this, &LspDocument::changeContent);
    connect(textEdit()->document(), &QTextDocument::blockCountChanged, this, &LspDocument::changeBlockCount);
}

void LspDocument::setLspClient(Lsp::Client *client)
{
    m_lspClient = client;
}

bool LspDocument::hasLspClient() const
{
    return m_lspClient != nullptr;
}

/**
 * Returns the symbol the cursor is in, or an empty symbol otherwise
 * The function is used to filter out the symbol
 *
 * Note that the returned `Symbol` pointer is only valid until the document
 * it originates from is deconstructed.
 */
Symbol *LspDocument::currentSymbol(std::function<bool(const Symbol &)> filterFunc) const
{
    const int pos = textEdit()->textCursor().position();

    auto symbolList = symbols();
    std::ranges::reverse(symbolList);
    for (auto symbol : symbolList) {
        if (symbol->range().contains(pos) && (!filterFunc || filterFunc(*symbol)))
            return symbol;
    }
    return {};
}

/**
 * Deletes the specified symbols text range, as well as leading whitespace
 * and trailing semicolon/newline character.
 */
void LspDocument::deleteSymbol(const Symbol &symbol)
{
    auto range = symbol.range();

    // Include any leading whitespace (excluding newlines).
    auto leading = Core::TextRange {range.start, range.start + 1};
    while (leading.start > 0) {
        leading.start--;
        leading.end--;
        selectRange(leading);

        if (selectedText() != " " && selectedText() != "\t") {
            break;
        }

        range.start--;
    }

    // Include a trailing semicolon and up to one trailing newline
    auto trailing = Core::TextRange {range.end, range.end + 1};
    selectRange(trailing);
    if (selectedText() == ";") {
        range.end++;

        trailing.start++;
        trailing.end++;
        selectRange(trailing);
    }

    if (selectedText() == "\n") {
        range.end++;
    }

    this->selectRange(range);
    this->deleteSelection();
}

/*!
 * \qmlmethod array<Symbol> LspDocument::symbols()
 * Returns the list of symbols in the current document.
 *
 * Note that the returned `Symbol` pointers are only valid until the document they
 * originate from is deconstructed.
 */
QVector<Core::Symbol *> LspDocument::symbols() const
{
    LOG("LspDocument::symbols");
    if (!checkClient())
        return {};
    return m_cache->symbols();
}

struct RegexpTransform
{
    QString from;
    QString to;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RegexpTransform, from, to);

struct Transforms
{
    std::vector<RegexpTransform> patterns;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Transforms, patterns);

void LspDocument::regexpTransform(const RegexpTransform &transform,
                                  const std::unordered_map<QString, QString> &regexpContext,
                                  std::function<bool(QRegularExpressionMatch, QTextCursor)> regexFilter)
{
    auto from = transform.from;
    auto to = transform.to;

    for (const auto &contextPair : regexpContext) {
        auto key = QString("${%1}").arg(contextPair.first);
        auto value = contextPair.second;
        from.replace(key, value);
        to.replace(key, value);
    }

    static QRegularExpression checkRegex("\\${(?<key>[a-zA-Z0-9_]+)}");
    auto match = checkRegex.match(from);
    auto key = match.captured("key");
    if (match.hasMatch() && !key.isNull()) {
        spdlog::warn("LspDocument::regexpTransform - Skipping Regex - Missing argument ${} to regex:\n{}",
                     QString("{%1}").arg(key).toStdString(), from.toStdString());
        return;
    }

    spdlog::trace("Running Regex conversion:\nFrom: {}\nTo: {}", from.toStdString(), to.toStdString());
    // Use the FindBackward flag, so that nested Regexp Transforms will
    // replace the "inner" item first.
    replaceAllRegexp(from, to, TextDocument::FindBackward | TextDocument::PreserveCase, regexFilter);
}

/*!
 * \qmlmethod LspDocument::transform(const QString &jsonFileName, object context)
 *
 * Runs a list of transformations defined in a JSON file.
 * The JSON file is loaded from the path specified in `jsonFileName`.
 *
 * A context object can be provided.
 * Any key in this object is used to provide additional context information to the transformation.
 * e.g. `{ symbol: "myobject" }` would replace all occurences of `${symbol}` in the json tranformation with `myobject`.
 */
void LspDocument::transform(const QString &jsonFileName, QVariantMap context /*  = {} */)
{
    erase_if(context, [](const std::pair<const QString &, QVariant &> keyvalue) {
        auto erase = !keyvalue.second.canConvert<QString>();
        if (erase) {
            spdlog::warn("LspDocument::transform: Removing non-string argument for key: {}",
                         keyvalue.first.toStdString());
        }
        return erase;
    });

    std::unordered_map<QString, QString> stdContext;
    QMapIterator<QString, QVariant> it(context);
    while (it.hasNext()) {
        auto item = it.next();
        stdContext[item.key()] = item.value().toString();
    }

    return transform(jsonFileName, stdContext);
}

void LspDocument::transform(const QString &jsonFileName, const std::unordered_map<QString, QString> &context)
{
    LOG("LspDocument::transform", jsonFileName);

    QFile file(jsonFileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        spdlog::error("LspDocument::transform - Could not open JSON file: '{}'", jsonFileName.toStdString());
        return;
    }
    QTextStream in(&file);

    nlohmann::json transformJson;
    try {
        transformJson = nlohmann::json::parse(in.readAll().toStdString());
    } catch (nlohmann::json::exception &exception) {
        spdlog::error("LspDocument::transform - JSON parsing failed: {}", exception.what());
        return;
    }

    try {
        auto transforms = transformJson.get<Transforms>();

        for (const auto &pattern : transforms.patterns) {
            regexpTransform(pattern, context);
        }
    } catch (nlohmann::json::exception &exception) {
        spdlog::error("LspDocument::transform - Not a valid Transform JSON: {}", exception.what());
        return;
    }
}

bool LspDocument::checkSymbolPosition(const Symbol *symbol, QRegularExpressionMatch match, QTextCursor cursor) const
{
    auto start = match.capturedStart("symbol");
    auto end = match.capturedEnd("symbol");
    // this means there was no "${symbol}" in the original search.
    // So just proceed as normal
    if (start == -1 || end == -1) {
        return true;
    }
    // the capture group is relative to the match, so we must add the match start.
    start += cursor.anchor();
    end += cursor.anchor();

    auto result =
        symbol->document() == this && start == symbol->selectionRange().start && end == symbol->selectionRange().end;
    spdlog::trace("LspDocument::checkSymbolPosition - Symbol position doesn't match RegexMatch.");
    return result;
}

bool LspDocument::checkReferencePosition(const QVector<Core::TextLocation> &references, QRegularExpressionMatch match,
                                         QTextCursor cursor) const
{
    auto start = match.capturedStart("reference");
    auto end = match.capturedEnd("reference");
    // this means there was no "${reference}" in the original search.
    // So just proceed as normal
    if (start == -1 || end == -1) {
        return true;
    }
    // the capture group is relative to the match, so we must add the match start.
    start += cursor.anchor();
    end += cursor.anchor();

    for (const auto &reference : references) {
        if (reference.document == this && start == reference.range.start && end == reference.range.end) {
            return true;
        }
    }
    spdlog::trace("LspDocument::transformSymbol - Found no references at the RegexMatch.");
    return false;
}

void LspDocument::transformSymbol(const Symbol *symbol, const QString &jsonFileName)
{
    if (!symbol) {
        spdlog::debug("LspDocument::transformSymbol - symbol is nullptr");
        return;
    }
    LOG("LspDocument::transform", jsonFileName);

    QFile file(jsonFileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        spdlog::error("LspDocument::transform - Could not open JSON file: '{}'", jsonFileName.toStdString());
        return;
    }
    QTextStream in(&file);

    nlohmann::json transformJson;
    try {
        transformJson = nlohmann::json::parse(in.readAll().toStdString());
    } catch (nlohmann::json::exception &exception) {
        spdlog::error("LspDocument::transform - JSON parsing failed: {}", exception.what());
        return;
    }

    std::unordered_map<QString, QString> context;
    context["reference"] = QString("(?<reference>%1)").arg(symbol->name());
    context["symbol"] = QString("(?<symbol>%1)").arg(symbol->name());
    context["name"] = symbol->name();

    try {
        auto transforms = transformJson.get<Transforms>();

        const auto references = symbol->references();

        for (const auto &pattern : transforms.patterns) {
            regexpTransform(pattern, context,
                            [this, symbol, &references](QRegularExpressionMatch match, QTextCursor cursor) {
                                return checkSymbolPosition(symbol, match, cursor)
                                    && checkReferencePosition(references, match, cursor);
                            });
        }
    } catch (nlohmann::json::exception &exception) {
        spdlog::error("LspDocument::transform - Not a valid Transform JSON: {}", exception.what());
        return;
    }
}

/*!
 * \qmlmethod Symbol LspDocument::symbolUnderCursor()
 * Returns the symbol that's at the current cursor position.
 *
 * This function may return symbols that are not returned by the `symbols()` or `currentSymbol()` function,
 * as these only return high-level symbols, like classes and functions, but not symbols within functions.
 * `symbolUnderCursor()` can however return these Symbols.
 */
const Core::Symbol *LspDocument::symbolUnderCursor() const
{
    const auto containsCursor = [this](const Core::Symbol *symbol) {
        return symbol->selectionRange().contains(textEdit()->textCursor().position());
    };

    const auto symbols = this->symbols();
    const auto symbolIter = kdalgorithms::find_if(symbols, containsCursor);
    if (symbolIter) {
        return *symbolIter;
    }

    auto hover = hoverWithRange(textEdit()->textCursor().position());
    if (hover.second) {
        return m_cache->inferSymbol(hover.first, hover.second.value());
    } else {
        spdlog::warn("LspDocument::symbolUnderCursor: Cannot infer Symbol - Language Server did not return a range!");
    }

    return nullptr;
}

/*!
 * \qmlmethod string LspDocument::hover()
 *
 * Returns information about the symbol at the current cursor position.
 * The result of this call is a plain string that may be formatted in Markdown.
 */
QString LspDocument::hover() const
{
    return hover(textEdit()->textCursor().position());
}

QString LspDocument::hover(int position, std::function<void(const QString &)> asyncCallback /*  = {} */) const
{
    if (asyncCallback) {
        return hoverWithRange(position,
                              [asyncCallback = std::move(asyncCallback)](const auto &hoverText, auto) {
                                  asyncCallback(hoverText);
                              })
            .first;
    } else {
        return hoverWithRange(position).first;
    }
}

std::pair<QString, std::optional<TextRange>> LspDocument::hoverWithRange(
    int position, std::function<void(const QString &, std::optional<TextRange>)> asyncCallback /*  = {} */) const
{
    LOG("LspDocument::hover");

    if (!checkClient())
        return {"", {}};

    Lsp::HoverParams params;
    params.textDocument.uri = toUri();
    params.position = fromPos(position);

    QPointer<const LspDocument> safeThis(this);

    auto convertResult = [safeThis](const auto &result) -> std::pair<QString, std::optional<TextRange>> {
        if (!std::holds_alternative<Lsp::Hover>(result)) {
            return {"", {}};
        }

        auto hover = std::get<Lsp::Hover>(result);

        std::optional<TextRange> range;
        if (hover.range && !safeThis.isNull()) {
            range = safeThis->toRange(hover.range.value());
        }

        Lsp::MarkupContent markupContent;
        if (const auto *content = std::get_if<Lsp::MarkupContent>(&hover.contents)) {
            return {QString::fromStdString(content->value), range};
        } else {
            spdlog::warn("LSP returned deprecated MarkedString type which is unsupported by Knut\n - Consider updating "
                         "your LSP server");
            return {"", {}};
        }
    };

    if (asyncCallback) {
        client()->hover(std::move(params),
                        [convertResult, asyncCallback = std::move(asyncCallback)](const auto result) {
                            auto hoverText = convertResult(result);
                            asyncCallback(hoverText.first, hoverText.second);
                        });
    } else {
        auto result = client()->hover(std::move(params));
        if (result) {
            // We can't have this in "convertResult", as that would spam the log due to Hover being called when
            // a Tooltip is requested.
            // See: TextView::eventFilter.
            if (!std::holds_alternative<Lsp::Hover>(result.value())) {
                spdlog::debug("LSP server returned no result for Hover");
            }
            return convertResult(result.value());
        }
    }

    return {"", {}};
}

/*!
 * \qmlmethod array<TextLocation> LspDocument::references()
 * Returns the list of references at the given position.
 */
QVector<Core::TextLocation> LspDocument::references(int position) const
{
    LOG("LspDocument::references");

    if (!checkClient()) {
        return {};
    }

    Lsp::ReferenceParams params;
    params.textDocument.uri = toUri();
    params.position = fromPos(position);

    QVector<Core::TextLocation> textLocations;
    if (auto result = client()->references(std::move(params))) {
        const auto &value = result.value();
        if (const auto *locations = std::get_if<std::vector<Lsp::Location>>(&value)) {
            return TextLocation::fromLsp(*locations);
        } else {
            spdlog::warn("LspDocument::references: Language server returned unsupported references type!");
        }
    } else {
        spdlog::warn("LspDocument::references: LSP call to references returned nothing!");
    }

    return textLocations;
}

/*!
 * \qmlmethod LspDocument::followSymbol()
 * Follows the symbol under the cursor.
 *
 * - Go to the declaration, if the symbol under cursor is a use
 * - Go to the declaration, if the symbol under cursor is a function definition
 * - Go to the definition, if the symbol under cursor is a function declaration
 */
Document *LspDocument::followSymbol()
{
    LOG("LspDocument::followSymbol");
    if (!checkClient())
        return {};

    // Set the cursor position to the beginning of any selected text.
    // That way, calling followSymbol twice in a row causes Clangd
    // to switch between delcaration and definition.
    auto cursor = textEdit()->textCursor();
    LOG_RETURN("document", followSymbol(cursor.selectionStart()));
}

/**
 * At least with clangd, the "declaration" LSP call acts like followSymbol, it will:
 * - Go to the declaration, if the symbol under cursor is a use
 * - Go to the declaration, if the symbol under cursor is a definition
 * - Go to the definition, if the symbol under cursor is a declaration
 */
Document *LspDocument::followSymbol(int pos)
{
    auto cursor = textEdit()->textCursor();
    cursor.setPosition(pos);

    Lsp::DeclarationParams params;
    params.textDocument.uri = toUri();
    params.position.line = cursor.blockNumber();
    params.position.character = cursor.positionInBlock();

    auto result = client()->declaration(std::move(params));

    Q_ASSERT(result.has_value());

    auto locations = std::vector<Lsp::Location>();

    if (std::holds_alternative<Lsp::Declaration>(*result)) {
        auto &declaration = std::get<Lsp::Declaration>(*result);
        if (std::holds_alternative<Lsp::Location>(declaration)) {
            auto location = std::get<Lsp::Location>(declaration);
            locations.push_back(location);
        } else if (std::holds_alternative<std::vector<Lsp::Location>>(declaration)) {
            locations = std::move(std::get<std::vector<Lsp::Location>>(declaration));
        }
    } else if (std::holds_alternative<std::vector<Lsp::DeclarationLink>>(*result)) {
        auto locationLinks = std::get<std::vector<Lsp::DeclarationLink>>(*result);
        for (const auto &link : locationLinks)
            locations.push_back({link.targetUri, link.targetSelectionRange});
    }

    if (locations.empty())
        return nullptr;

    if (locations.size() > 1)
        spdlog::warn("LspDocument::followSymbol: Multiple locations returned!");
    // Heuristic: If multiple locations were found, use the last one.
    auto location = locations.back();

    auto url = QUrl::fromEncoded(QByteArray::fromStdString(location.uri));

    Q_ASSERT(url.isLocalFile());
    auto filepath = url.toLocalFile();

    auto *document = Project::instance()->open(filepath);

    if (document) {
        auto *lspDocument = qobject_cast<LspDocument *>(document);
        if (lspDocument) {
            lspDocument->selectRange(lspDocument->toRange(location.range));
        } else {
            spdlog::warn("LspDocument::followSymbol: Opened document '{}' is not an LspDocument",
                         document->fileName().toStdString());
        }
    }

    return document;
}

/*!
 * \qmlmethod LspDocument::switchDeclarationDefinition()
 * Switches between the function declaration or definition.
 * \todo
 */
Document *LspDocument::switchDeclarationDefinition()
{
    LOG("LspDocument::switchDeclarationDefinition");
    if (!checkClient())
        return {};

    auto cursor = textEdit()->textCursor();
    auto symbolList = symbols();

    auto currentFunction = kdalgorithms::find_if(symbolList, [&cursor](const auto &symbol) {
        auto isInRange = symbol->range().start <= cursor.position() && cursor.position() <= symbol->range().end;
        return isInRange && symbol->isFunction();
    });

    if (!currentFunction) {
        spdlog::info("LspDocument::switchDeclarationDefinition: Cursor is currently not within a function!");
        return nullptr;
    }

    LOG_RETURN("document", followSymbol((*currentFunction)->selectionRange().start));
}

/*!
 * \qmlmethod LspDocument::selectSymbol(string name, int options = TextDocument.NoFindFlags)
 * Selects a symbol based on its `name`, using different find `options`.
 *
 * - `TextDocument.FindCaseSensitively`: match case
 * - `TextDocument.FindWholeWords`: match only fully qualified symbol
 * - `TextDocument.FindRegexp`: use a regexp
 *
 * If no symbols are found, do nothing.
 */
void LspDocument::selectSymbol(const QString &name, int options)
{
    LOG("LspDocument::selectSymbol", LOG_ARG("text", name), options);
    if (!checkClient())
        return;

    if (auto symbol = findSymbol(name, options))
        selectRange(symbol->selectionRange());
}

/*!
 * \qmlmethod Symbol LspDocument::findSymbol(string name, int options = TextDocument.NoFindFlags)
 * Finds a symbol based on its `name`, using different find `options`.
 *
 * - `TextDocument.FindCaseSensitively`: match case
 * - `TextDocument.FindWholeWords`: match only fully qualified symbol
 * - `TextDocument.FindRegexp`: use a regexp
 *
 * Note that the returned `Symbol` pointer is only valid until the document it originates
 * from is deconstructed.
 */
Symbol *LspDocument::findSymbol(const QString &name, int options) const
{
    LOG("LspDocument::findSymbol", LOG_ARG("text", name), options);
    if (!checkClient())
        return {};

    const auto &symbols = m_cache->symbols();
    const auto regexp = (options & FindRegexp) ? createRegularExpression(name, options) : QRegularExpression {};
    auto byName = [name, options, regexp](Symbol *symbol) {
        if (options & FindWholeWords)
            return symbol->name().compare(name,
                                          (options & FindCaseSensitively) ? Qt::CaseSensitive : Qt::CaseInsensitive)
                == 0;
        else if (options & FindRegexp)
            return regexp.match(symbol->name()).hasMatch();
        else
            return symbol->name().contains(name,
                                           (options & FindCaseSensitively) ? Qt::CaseSensitive : Qt::CaseInsensitive);
    };
    auto it = std::ranges::find_if(symbols, byName);
    if (it != symbols.end())
        return *it;
    return nullptr;
}

void LspDocument::didOpen()
{
    if (!m_lspClient)
        return;

    Lsp::DidOpenTextDocumentParams params;
    params.textDocument.uri = toUri();
    params.textDocument.version = revision();
    params.textDocument.text = textEdit()->toPlainText().toStdString();
    params.textDocument.languageId = m_lspClient->languageId();

    m_lspClient->didOpen(std::move(params));
}

void LspDocument::didClose()
{
    if (!m_lspClient)
        return;

    Lsp::DidCloseTextDocumentParams params;
    params.textDocument.uri = toUri();

    m_lspClient->didClose(std::move(params));
}

Lsp::Client *LspDocument::client() const
{
    return m_lspClient;
}

std::string LspDocument::toUri() const
{
    return QUrl::fromLocalFile(fileName()).toString().toStdString();
}

int LspDocument::toPos(const Lsp::Position &pos) const
{
    // Internally, columns are 0-based, like in LSP
    const int blockNumber = qMin((int)pos.line, textEdit()->document()->blockCount() - 1);
    const QTextBlock &block = textEdit()->document()->findBlockByNumber(blockNumber);
    if (block.isValid()) {
        QTextCursor cursor(block);
        cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, pos.character);
        return cursor.position();
    }
    return 0;
}

Lsp::Position LspDocument::fromPos(int pos) const
{
    Lsp::Position position;

    auto cursor = textEdit()->textCursor();
    cursor.setPosition(pos, QTextCursor::MoveAnchor);

    position.line = cursor.blockNumber();
    position.character = cursor.positionInBlock();
    return position;
}

TextRange LspDocument::toRange(const Lsp::Range &range) const
{
    return {toPos(range.start), toPos(range.end)};
}

/*!
 * \qmlmethod array<QueryMatch> LspDocument::query(string query)
 * Runs the `query` passed in parameter and returns the list of matches.
 *
 * The query is using the [TreeSitter](https://tree-sitter.github.io/tree-sitter/) query, you can find more information
 * on this page: [Pattern Matching with
 * Queries](https://tree-sitter.github.io/tree-sitter/using-parsers#pattern-matching-with-queries).
 */

QVector<QueryMatch> LspDocument::query(const QString &query)
{
    LOG("LspDocument::query", LOG_ARG("query", query));

    std::shared_ptr<treesitter::Query> tsQuery;
    try {
        tsQuery = std::make_shared<treesitter::Query>(tree_sitter_cpp(), query);
    } catch (treesitter::Query::Error error) {
        spdlog::error("LspDocument::query: Failed to parse query `{}` error: {} at: ", query.toStdString(),
                      error.description.toStdString(), error.utf8_offset);
        return {};
    }

    auto parser = treesitter::Parser(tree_sitter_cpp());
    auto tree = parser.parseString(text());

    if (!tree) {
        spdlog::error("LspDocument::query: Failed to parse document `{}`", fileName().toStdString());
        return {};
    }

    treesitter::QueryCursor cursor;
    cursor.execute(tsQuery, tree->rootNode(), std::make_unique<treesitter::Predicates>(text()));
    auto matches = cursor.allRemainingMatches();

    return kdalgorithms::transformed<QVector<QueryMatch>>(matches, [this](const treesitter::QueryMatch &match) {
        return QueryMatch(*this, match);
    });
}

int LspDocument::revision() const
{
    return m_revision;
}

bool LspDocument::checkClient() const
{
    Q_ASSERT(textEdit());
    if (!client()) {
        spdlog::error("LspDocument {} has no LSP client - API not available", fileName().toStdString());
        return false;
    }
    return true;
}

void LspDocument::changeBlockCount(int newBlockCount)
{
    spdlog::warn("new block count: {}", newBlockCount);
}

void LspDocument::changeContent(int position, int charsRemoved, int charsAdded)
{
    Q_UNUSED(position)
    Q_UNUSED(charsRemoved)
    Q_UNUSED(charsAdded)
    m_cache->clear();

    // TODO: Keep copy of previous string around, so we can find the oldEndPosition.
    // const auto document = textEdit()->document();
    // const auto startblock = document->findBlock(position);
    // spdlog::warn("start point: {}, {}", startblock.blockNumber(), position - startblock.position());

    // const auto newEndPosition = position + charsAdded;
    // const auto newEndBlock = document->findBlock(newEndPosition);
    // spdlog::warn("new end point: {}, {}", newEndBlock.blockNumber(), newEndPosition - newEndBlock.position());

    // const auto plain = document->toPlainText();
    // spdlog::warn("added: {}", plain.sliced(position, charsAdded).toStdString());

    if (!checkClient()) {
        return;
    }

    if (client()->canSendDocumentChanges(Lsp::TextDocumentSyncKind::Full)
        || client()->canSendDocumentChanges(Lsp::TextDocumentSyncKind::Incremental)) {
        // TODO: We currently always send the entire document to the Language server, even
        // if it suppports incremental changes.
        // Change this, so we also send incremental updates.
        //
        // This currently isn't implemented, as changeContent only gets called *after*
        // the change has happened, but the LSP server needs the locations from *before* the change
        // has happened, which can no longer be queried.

        Lsp::VersionedTextDocumentIdentifier document;
        document.version = ++m_revision;
        document.uri = toUri();

        std::vector<Lsp::TextDocumentContentChangeEvent> events;

        // Set text
        Lsp::TextDocumentContentChangeEventFull event {};
        event.text = text().toStdString();

        events.push_back(std::move(event));

        Lsp::DidChangeTextDocumentParams params;
        params.textDocument = document;
        params.contentChanges = events;

        client()->didChange(std::move(params));
    } else {
        spdlog::error("LSP server does not support Document changes!");
    }
}

} // namespace Core

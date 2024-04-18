// File generated by spec2cpp tool
// DO NOT MAKE ANY CHANGES HERE

#pragma once

#include "types.h"
#include "utils/json.h"

namespace Lsp {

JSONIFY_ENUM(SemanticTokenTypes,
             {
                 {SemanticTokenTypes::Namespace, "namespace"},
                 {SemanticTokenTypes::Type, "type"},
                 {SemanticTokenTypes::Class, "class"},
                 {SemanticTokenTypes::Enum, "enum"},
                 {SemanticTokenTypes::Interface, "interface"},
                 {SemanticTokenTypes::Struct, "struct"},
                 {SemanticTokenTypes::TypeParameter, "typeParameter"},
                 {SemanticTokenTypes::Parameter, "parameter"},
                 {SemanticTokenTypes::Variable, "variable"},
                 {SemanticTokenTypes::Property, "property"},
                 {SemanticTokenTypes::EnumMember, "enumMember"},
                 {SemanticTokenTypes::Event, "event"},
                 {SemanticTokenTypes::Function, "function"},
                 {SemanticTokenTypes::Method, "method"},
                 {SemanticTokenTypes::Macro, "macro"},
                 {SemanticTokenTypes::Keyword, "keyword"},
                 {SemanticTokenTypes::Modifier, "modifier"},
                 {SemanticTokenTypes::Comment, "comment"},
                 {SemanticTokenTypes::String, "string"},
                 {SemanticTokenTypes::Number, "number"},
                 {SemanticTokenTypes::Regexp, "regexp"},
                 {SemanticTokenTypes::Operator, "operator"},
                 {SemanticTokenTypes::Decorator, "decorator"},
             })

JSONIFY_ENUM(SemanticTokenModifiers,
             {
                 {SemanticTokenModifiers::Declaration, "declaration"},
                 {SemanticTokenModifiers::Definition, "definition"},
                 {SemanticTokenModifiers::Readonly, "readonly"},
                 {SemanticTokenModifiers::Static, "static"},
                 {SemanticTokenModifiers::Deprecated, "deprecated"},
                 {SemanticTokenModifiers::Abstract, "abstract"},
                 {SemanticTokenModifiers::Async, "async"},
                 {SemanticTokenModifiers::Modification, "modification"},
                 {SemanticTokenModifiers::Documentation, "documentation"},
                 {SemanticTokenModifiers::DefaultLibrary, "defaultLibrary"},
             })

JSONIFY_ENUM(FoldingRangeKind,
             {
                 {FoldingRangeKind::Comment, "comment"},
                 {FoldingRangeKind::Imports, "imports"},
                 {FoldingRangeKind::Region, "region"},
             })

JSONIFY_ENUM(UniquenessLevel,
             {
                 {UniquenessLevel::Document, "document"},
                 {UniquenessLevel::Project, "project"},
                 {UniquenessLevel::Group, "group"},
                 {UniquenessLevel::Scheme, "scheme"},
                 {UniquenessLevel::Global, "global"},
             })

JSONIFY_ENUM(MonikerKind,
             {
                 {MonikerKind::Import, "import"},
                 {MonikerKind::Export, "export"},
                 {MonikerKind::Local, "local"},
             })

JSONIFY_ENUM(CodeActionKind,
             {
                 {CodeActionKind::Empty, ""},
                 {CodeActionKind::QuickFix, "quickfix"},
                 {CodeActionKind::Refactor, "refactor"},
                 {CodeActionKind::RefactorExtract, "refactor.extract"},
                 {CodeActionKind::RefactorInline, "refactor.inline"},
                 {CodeActionKind::RefactorRewrite, "refactor.rewrite"},
                 {CodeActionKind::Source, "source"},
                 {CodeActionKind::SourceOrganizeImports, "source.organizeImports"},
                 {CodeActionKind::SourceFixAll, "source.fixAll"},
             })

JSONIFY_ENUM(TraceValues,
             {
                 {TraceValues::Off, "off"},
                 {TraceValues::Messages, "messages"},
                 {TraceValues::Verbose, "verbose"},
             })

JSONIFY_ENUM(MarkupKind,
             {
                 {MarkupKind::PlainText, "plaintext"},
                 {MarkupKind::Markdown, "markdown"},
             })

JSONIFY_ENUM(PositionEncodingKind,
             {
                 {PositionEncodingKind::UTF8, "utf-8"},
                 {PositionEncodingKind::UTF16, "utf-16"},
                 {PositionEncodingKind::UTF32, "utf-32"},
             })

JSONIFY_ENUM(FileOperationPatternKind,
             {
                 {FileOperationPatternKind::File, "file"},
                 {FileOperationPatternKind::Folder, "folder"},
             })

JSONIFY_ENUM(ResourceOperationKind,
             {
                 {ResourceOperationKind::Create, "create"},
                 {ResourceOperationKind::Rename, "rename"},
                 {ResourceOperationKind::Delete, "delete"},
             })

JSONIFY_ENUM(FailureHandlingKind,
             {
                 {FailureHandlingKind::Abort, "abort"},
                 {FailureHandlingKind::Transactional, "transactional"},
                 {FailureHandlingKind::TextOnlyTransactional, "textOnlyTransactional"},
                 {FailureHandlingKind::Undo, "undo"},
             })

JSONIFY_ENUM(TokenFormat,
             {
                 {TokenFormat::Relative, "relative"},
             })

JSONIFY(ImplementationParams, workDoneToken, partialResultToken, textDocument, position)

JSONIFY(Location, uri, range)

JSONIFY(ImplementationRegistrationOptions, id, documentSelector, workDoneProgress)

JSONIFY(TypeDefinitionParams, workDoneToken, partialResultToken, textDocument, position)

JSONIFY(TypeDefinitionRegistrationOptions, id, documentSelector, workDoneProgress)

JSONIFY(WorkspaceFolder, uri, name)

JSONIFY(DidChangeWorkspaceFoldersParams, event)

JSONIFY(ConfigurationParams, items)

JSONIFY(PartialResultParams, partialResultToken)

JSONIFY(DocumentColorParams, textDocument, workDoneToken, partialResultToken)

JSONIFY(ColorInformation, range, color)

JSONIFY(DocumentColorRegistrationOptions, id, documentSelector, workDoneProgress)

JSONIFY(ColorPresentationParams, textDocument, color, range, workDoneToken, partialResultToken)

JSONIFY(ColorPresentation, label, textEdit, additionalTextEdits)

JSONIFY(WorkDoneProgressOptions, workDoneProgress)

JSONIFY(TextDocumentRegistrationOptions, documentSelector)

JSONIFY(FoldingRangeParams, textDocument, workDoneToken, partialResultToken)

JSONIFY(FoldingRange, startLine, startCharacter, endLine, endCharacter, kind, collapsedText)

JSONIFY(FoldingRangeRegistrationOptions, id, documentSelector, workDoneProgress)

JSONIFY(DeclarationParams, workDoneToken, partialResultToken, textDocument, position)

JSONIFY(DeclarationRegistrationOptions, id, workDoneProgress, documentSelector)

JSONIFY(SelectionRangeParams, textDocument, positions, workDoneToken, partialResultToken)

JSONIFY_FWD(SelectionRange)

JSONIFY(SelectionRangeRegistrationOptions, id, workDoneProgress, documentSelector)

JSONIFY(WorkDoneProgressCreateParams, token)

JSONIFY(WorkDoneProgressCancelParams, token)

JSONIFY(CallHierarchyPrepareParams, workDoneToken, textDocument, position)

JSONIFY(CallHierarchyItem, name, kind, tags, detail, uri, range, selectionRange, data)

JSONIFY(CallHierarchyRegistrationOptions, id, documentSelector, workDoneProgress)

JSONIFY(CallHierarchyIncomingCallsParams, item, workDoneToken, partialResultToken)

JSONIFY(CallHierarchyIncomingCall, from, fromRanges)

JSONIFY(CallHierarchyOutgoingCallsParams, item, workDoneToken, partialResultToken)

JSONIFY(CallHierarchyOutgoingCall, to, fromRanges)

JSONIFY(SemanticTokensParams, textDocument, workDoneToken, partialResultToken)

JSONIFY(SemanticTokens, resultId, data)

JSONIFY(SemanticTokensPartialResult, data)

JSONIFY(SemanticTokensRegistrationOptions, id, documentSelector, legend, range, full, workDoneProgress)

JSONIFY(SemanticTokensDeltaParams, textDocument, previousResultId, workDoneToken, partialResultToken)

JSONIFY(SemanticTokensDelta, resultId, edits)

JSONIFY(SemanticTokensDeltaPartialResult, edits)

JSONIFY(SemanticTokensRangeParams, textDocument, range, workDoneToken, partialResultToken)

JSONIFY(ShowDocumentParams, uri, external, takeFocus, selection)

JSONIFY(ShowDocumentResult, success)

JSONIFY(LinkedEditingRangeParams, workDoneToken, textDocument, position)

JSONIFY(LinkedEditingRanges, ranges, wordPattern)

JSONIFY(LinkedEditingRangeRegistrationOptions, id, documentSelector, workDoneProgress)

JSONIFY(CreateFilesParams, files)

JSONIFY(WorkspaceEdit::ChangesType, propertyMap)

JSONIFY_FWD(WorkspaceEdit::ChangeAnnotationsType)
JSONIFY(WorkspaceEdit, changes, documentChanges, changeAnnotations)

JSONIFY(FileOperationRegistrationOptions, filters)

JSONIFY(RenameFilesParams, files)

JSONIFY(DeleteFilesParams, files)

JSONIFY(MonikerParams, workDoneToken, partialResultToken, textDocument, position)

JSONIFY(Moniker, scheme, identifier, unique, kind)

JSONIFY(MonikerRegistrationOptions, documentSelector, workDoneProgress)

JSONIFY(TypeHierarchyPrepareParams, workDoneToken, textDocument, position)

JSONIFY(TypeHierarchyItem, name, kind, tags, detail, uri, range, selectionRange, data)

JSONIFY(TypeHierarchyRegistrationOptions, id, documentSelector, workDoneProgress)

JSONIFY(TypeHierarchySupertypesParams, item, workDoneToken, partialResultToken)

JSONIFY(TypeHierarchySubtypesParams, item, workDoneToken, partialResultToken)

JSONIFY(InlineValueParams, textDocument, range, context, workDoneToken)

JSONIFY(InlineValueRegistrationOptions, id, workDoneProgress, documentSelector)

JSONIFY(InlayHintParams, textDocument, range, workDoneToken)

JSONIFY(InlayHint, position, label, kind, textEdits, tooltip, paddingLeft, paddingRight, data)

JSONIFY(InlayHintRegistrationOptions, id, resolveProvider, workDoneProgress, documentSelector)

JSONIFY(DocumentDiagnosticParams, textDocument, identifier, previousResultId, workDoneToken, partialResultToken)

JSONIFY(DocumentDiagnosticReportPartialResult, relatedDocuments)

JSONIFY(DiagnosticServerCancellationData, retriggerRequest)

JSONIFY(DiagnosticRegistrationOptions, id, documentSelector, identifier, interFileDependencies, workspaceDiagnostics,
        workDoneProgress)

JSONIFY(WorkspaceDiagnosticParams, identifier, previousResultIds, workDoneToken, partialResultToken)

JSONIFY(WorkspaceDiagnosticReport, items)

JSONIFY(WorkspaceDiagnosticReportPartialResult, items)

JSONIFY(DidOpenNotebookDocumentParams, notebookDocument, cellTextDocuments)

JSONIFY(DidChangeNotebookDocumentParams, notebookDocument, change)

JSONIFY(DidSaveNotebookDocumentParams, notebookDocument)

JSONIFY(DidCloseNotebookDocumentParams, notebookDocument, cellTextDocuments)

JSONIFY(RegistrationParams, registrations)

JSONIFY(UnregistrationParams, unregisterations)

JSONIFY(InitializeParams, processId, clientInfo, locale, rootPath, rootUri, capabilities, initializationOptions, trace,
        workDoneToken, workspaceFolders)

JSONIFY(InitializeResult::ServerInfoType, name, version)
JSONIFY(InitializeResult, capabilities, serverInfo)

JSONIFY(InitializeError, retry)

JSONIFY_EMPTY(InitializedParams)

JSONIFY(DidChangeConfigurationParams, settings)

JSONIFY(DidChangeConfigurationRegistrationOptions, section)

JSONIFY(ShowMessageParams, type, message)

JSONIFY(ShowMessageRequestParams, type, message, actions)

JSONIFY(MessageActionItem, title)

JSONIFY(LogMessageParams, type, message)

JSONIFY(DidOpenTextDocumentParams, textDocument)

JSONIFY(DidChangeTextDocumentParams, textDocument, contentChanges)

JSONIFY(TextDocumentChangeRegistrationOptions, syncKind, documentSelector)

JSONIFY(DidCloseTextDocumentParams, textDocument)

JSONIFY(DidSaveTextDocumentParams, textDocument, text)

JSONIFY(TextDocumentSaveRegistrationOptions, documentSelector, includeText)

JSONIFY(WillSaveTextDocumentParams, textDocument, reason)

JSONIFY(TextEdit, range, newText)

JSONIFY(DidChangeWatchedFilesParams, changes)

JSONIFY(DidChangeWatchedFilesRegistrationOptions, watchers)

JSONIFY(PublishDiagnosticsParams, uri, version, diagnostics)

JSONIFY(CompletionParams, context, workDoneToken, partialResultToken, textDocument, position)

JSONIFY(CompletionItem, label, labelDetails, kind, tags, detail, documentation, deprecated, preselect, sortText,
        filterText, insertText, insertTextFormat, insertTextMode, textEdit, textEditText, additionalTextEdits,
        commitCharacters, command, data)

JSONIFY(CompletionList::ItemDefaultsType::EditRangeType, insert, replace)
JSONIFY(CompletionList::ItemDefaultsType, commitCharacters, editRange, insertTextFormat, insertTextMode, data)
JSONIFY(CompletionList, isIncomplete, itemDefaults, items)

JSONIFY(CompletionRegistrationOptions, documentSelector, triggerCharacters, allCommitCharacters, resolveProvider,
        completionItem, workDoneProgress)

JSONIFY(HoverParams, workDoneToken, textDocument, position)

JSONIFY(Hover, contents, range)

JSONIFY(HoverRegistrationOptions, documentSelector, workDoneProgress)

JSONIFY(SignatureHelpParams, context, workDoneToken, textDocument, position)

JSONIFY(SignatureHelp, signatures, activeSignature, activeParameter)

JSONIFY(SignatureHelpRegistrationOptions, documentSelector, triggerCharacters, retriggerCharacters, workDoneProgress)

JSONIFY(DefinitionParams, workDoneToken, partialResultToken, textDocument, position)

JSONIFY(DefinitionRegistrationOptions, documentSelector, workDoneProgress)

JSONIFY(ReferenceParams, context, workDoneToken, partialResultToken, textDocument, position)

JSONIFY(ReferenceRegistrationOptions, documentSelector, workDoneProgress)

JSONIFY(DocumentHighlightParams, workDoneToken, partialResultToken, textDocument, position)

JSONIFY(DocumentHighlight, range, kind)

JSONIFY(DocumentHighlightRegistrationOptions, documentSelector, workDoneProgress)

JSONIFY(DocumentSymbolParams, textDocument, workDoneToken, partialResultToken)

JSONIFY(SymbolInformation, deprecated, location, name, kind, tags, containerName)

JSONIFY(DocumentSymbol, name, detail, kind, tags, deprecated, range, selectionRange, children)

JSONIFY(DocumentSymbolRegistrationOptions, documentSelector, label, workDoneProgress)

JSONIFY(CodeActionParams, textDocument, range, context, workDoneToken, partialResultToken)

JSONIFY(Command, title, command, arguments)

JSONIFY(CodeAction::DisabledType, reason)
JSONIFY(CodeAction, title, kind, diagnostics, isPreferred, disabled, edit, command, data)

JSONIFY(CodeActionRegistrationOptions, documentSelector, codeActionKinds, resolveProvider, workDoneProgress)

JSONIFY(WorkspaceSymbolParams, query, workDoneToken, partialResultToken)

JSONIFY(WorkspaceSymbol::LocationType, uri)
JSONIFY(WorkspaceSymbol, location, data, name, kind, tags, containerName)

JSONIFY(WorkspaceSymbolRegistrationOptions, resolveProvider, workDoneProgress)

JSONIFY(CodeLensParams, textDocument, workDoneToken, partialResultToken)

JSONIFY(CodeLens, range, command, data)

JSONIFY(CodeLensRegistrationOptions, documentSelector, resolveProvider, workDoneProgress)

JSONIFY(DocumentLinkParams, textDocument, workDoneToken, partialResultToken)

JSONIFY(DocumentLink, range, target, tooltip, data)

JSONIFY(DocumentLinkRegistrationOptions, documentSelector, resolveProvider, workDoneProgress)

JSONIFY(DocumentFormattingParams, textDocument, options, workDoneToken)

JSONIFY(DocumentFormattingRegistrationOptions, documentSelector, workDoneProgress)

JSONIFY(DocumentRangeFormattingParams, textDocument, range, options, workDoneToken)

JSONIFY(DocumentRangeFormattingRegistrationOptions, documentSelector, workDoneProgress)

JSONIFY(DocumentOnTypeFormattingParams, textDocument, position, ch, options)

JSONIFY(DocumentOnTypeFormattingRegistrationOptions, documentSelector, firstTriggerCharacter, moreTriggerCharacter)

JSONIFY(RenameParams, textDocument, position, newName, workDoneToken)

JSONIFY(RenameRegistrationOptions, documentSelector, prepareProvider, workDoneProgress)

JSONIFY(PrepareRenameParams, workDoneToken, textDocument, position)

JSONIFY(ExecuteCommandParams, command, arguments, workDoneToken)

JSONIFY(ExecuteCommandRegistrationOptions, commands, workDoneProgress)

JSONIFY(ApplyWorkspaceEditParams, label, edit)

JSONIFY(ApplyWorkspaceEditResult, applied, failureReason, failedChange)

JSONIFY(WorkDoneProgressBegin, kind, title, cancellable, message, percentage)

JSONIFY(WorkDoneProgressReport, kind, cancellable, message, percentage)

JSONIFY(WorkDoneProgressEnd, kind, message)

JSONIFY(SetTraceParams, value)

JSONIFY(LogTraceParams, message, verbose)

JSONIFY(CancelParams, id)

JSONIFY(ProgressParams, token, value)

JSONIFY(TextDocumentPositionParams, textDocument, position)

JSONIFY(WorkDoneProgressParams, workDoneToken)

JSONIFY(LocationLink, originSelectionRange, targetUri, targetRange, targetSelectionRange)

JSONIFY(Range, start, end)

JSONIFY(ImplementationOptions, workDoneProgress)

JSONIFY(StaticRegistrationOptions, id)

JSONIFY(TypeDefinitionOptions, workDoneProgress)

JSONIFY(WorkspaceFoldersChangeEvent, added, removed)

JSONIFY(ConfigurationItem, scopeUri, section)

JSONIFY(TextDocumentIdentifier, uri)

JSONIFY(Color, red, green, blue, alpha)

JSONIFY(DocumentColorOptions, workDoneProgress)

JSONIFY(FoldingRangeOptions, workDoneProgress)

JSONIFY(DeclarationOptions, workDoneProgress)

JSONIFY(Position, line, character)

JSONIFY(SelectionRangeOptions, workDoneProgress)

JSONIFY(CallHierarchyOptions, workDoneProgress)

JSONIFY_EMPTY(SemanticTokensOptions::RangeType)
JSONIFY(SemanticTokensOptions::FullType, delta)
JSONIFY(SemanticTokensOptions, legend, range, full, workDoneProgress)

JSONIFY(SemanticTokensEdit, start, deleteCount, data)

JSONIFY(LinkedEditingRangeOptions, workDoneProgress)

JSONIFY(FileCreate, uri)

JSONIFY(TextDocumentEdit, textDocument, edits)

JSONIFY(CreateFile, kind, uri, options, kind, annotationId)

JSONIFY(RenameFile, kind, oldUri, newUri, options, kind, annotationId)

JSONIFY(DeleteFile, kind, uri, options, kind, annotationId)

JSONIFY(ChangeAnnotation, label, needsConfirmation, description)

JSONIFY(FileOperationFilter, scheme, pattern)

JSONIFY(FileRename, oldUri, newUri)

JSONIFY(FileDelete, uri)

JSONIFY(MonikerOptions, workDoneProgress)

JSONIFY(TypeHierarchyOptions, workDoneProgress)

JSONIFY(InlineValueContext, frameId, stoppedLocation)

JSONIFY(InlineValueText, range, text)

JSONIFY(InlineValueVariableLookup, range, variableName, caseSensitiveLookup)

JSONIFY(InlineValueEvaluatableExpression, range, expression)

JSONIFY(InlineValueOptions, workDoneProgress)

JSONIFY(InlayHintLabelPart, value, tooltip, location, command)

JSONIFY(MarkupContent, kind, value)

JSONIFY(InlayHintOptions, resolveProvider, workDoneProgress)

JSONIFY(RelatedFullDocumentDiagnosticReport, relatedDocuments, kind, resultId, items)

JSONIFY(RelatedUnchangedDocumentDiagnosticReport, relatedDocuments, kind, resultId)

JSONIFY(FullDocumentDiagnosticReport, kind, resultId, items)

JSONIFY(UnchangedDocumentDiagnosticReport, kind, resultId)

JSONIFY(DiagnosticOptions, identifier, interFileDependencies, workspaceDiagnostics, workDoneProgress)

JSONIFY(PreviousResultId, uri, value)

JSONIFY(NotebookDocument, uri, notebookType, version, metadata, cells)

JSONIFY(TextDocumentItem, uri, languageId, version, text)

JSONIFY(VersionedNotebookDocumentIdentifier, version, uri)

JSONIFY(NotebookDocumentChangeEvent::CellsType::StructureType, array, didOpen, didClose)
JSONIFY(NotebookDocumentChangeEvent::CellsType::TextContentType, document, changes)
JSONIFY(NotebookDocumentChangeEvent::CellsType, structure, data, textContent)
JSONIFY(NotebookDocumentChangeEvent, metadata, cells)

JSONIFY(NotebookDocumentIdentifier, uri)

JSONIFY(Registration, id, method, registerOptions)

JSONIFY(Unregistration, id, method)

JSONIFY(_InitializeParams::ClientInfoType, name, version)
JSONIFY(_InitializeParams, processId, clientInfo, locale, rootPath, rootUri, capabilities, initializationOptions, trace,
        workDoneToken)

JSONIFY(WorkspaceFoldersInitializeParams, workspaceFolders)

JSONIFY(ServerCapabilities::WorkspaceType, workspaceFolders, fileOperations)
JSONIFY(ServerCapabilities, positionEncoding, textDocumentSync, notebookDocumentSync, completionProvider, hoverProvider,
        signatureHelpProvider, declarationProvider, definitionProvider, typeDefinitionProvider, implementationProvider,
        referencesProvider, documentHighlightProvider, documentSymbolProvider, codeActionProvider, codeLensProvider,
        documentLinkProvider, colorProvider, workspaceSymbolProvider, documentFormattingProvider,
        documentRangeFormattingProvider, documentOnTypeFormattingProvider, renameProvider, foldingRangeProvider,
        selectionRangeProvider, executeCommandProvider, callHierarchyProvider, linkedEditingRangeProvider,
        semanticTokensProvider, monikerProvider, typeHierarchyProvider, inlineValueProvider, inlayHintProvider,
        diagnosticProvider, workspace, experimental)

JSONIFY(VersionedTextDocumentIdentifier, version, uri)

JSONIFY(SaveOptions, includeText)

JSONIFY(FileEvent, uri, type)

JSONIFY(FileSystemWatcher, globPattern, kind)

JSONIFY(Diagnostic, range, severity, code, codeDescription, source, message, tags, relatedInformation, data)

JSONIFY(CompletionContext, triggerKind, triggerCharacter)

JSONIFY(CompletionItemLabelDetails, detail, description)

JSONIFY(InsertReplaceEdit, newText, insert, replace)

JSONIFY(CompletionOptions::CompletionItemType, labelDetailsSupport)
JSONIFY(CompletionOptions, triggerCharacters, allCommitCharacters, resolveProvider, completionItem, workDoneProgress)

JSONIFY(HoverOptions, workDoneProgress)

JSONIFY(SignatureHelpContext, triggerKind, triggerCharacter, isRetrigger, activeSignatureHelp)

JSONIFY(SignatureInformation, label, documentation, parameters, activeParameter)

JSONIFY(SignatureHelpOptions, triggerCharacters, retriggerCharacters, workDoneProgress)

JSONIFY(DefinitionOptions, workDoneProgress)

JSONIFY(ReferenceContext, includeDeclaration)

JSONIFY(ReferenceOptions, workDoneProgress)

JSONIFY(DocumentHighlightOptions, workDoneProgress)

JSONIFY(BaseSymbolInformation, name, kind, tags, containerName)

JSONIFY(DocumentSymbolOptions, label, workDoneProgress)

JSONIFY(CodeActionContext, diagnostics, only, triggerKind)

JSONIFY(CodeActionOptions, codeActionKinds, resolveProvider, workDoneProgress)

JSONIFY(WorkspaceSymbolOptions, resolveProvider, workDoneProgress)

JSONIFY(CodeLensOptions, resolveProvider, workDoneProgress)

JSONIFY(DocumentLinkOptions, resolveProvider, workDoneProgress)

JSONIFY_FWD(FormattingOptions)

JSONIFY(DocumentFormattingOptions, workDoneProgress)

JSONIFY(DocumentRangeFormattingOptions, workDoneProgress)

JSONIFY(DocumentOnTypeFormattingOptions, firstTriggerCharacter, moreTriggerCharacter)

JSONIFY(RenameOptions, prepareProvider, workDoneProgress)

JSONIFY(ExecuteCommandOptions, commands, workDoneProgress)

JSONIFY(SemanticTokensLegend, tokenTypes, tokenModifiers)

JSONIFY(OptionalVersionedTextDocumentIdentifier, version, uri)

JSONIFY(AnnotatedTextEdit, annotationId, range, newText)

JSONIFY(ResourceOperation, kind, annotationId)

JSONIFY(CreateFileOptions, overwrite, ignoreIfExists)

JSONIFY(RenameFileOptions, overwrite, ignoreIfExists)

JSONIFY(DeleteFileOptions, recursive, ignoreIfNotExists)

JSONIFY(FileOperationPattern, glob, matches, options)

JSONIFY(WorkspaceFullDocumentDiagnosticReport, uri, version, kind, resultId, items)

JSONIFY(WorkspaceUnchangedDocumentDiagnosticReport, uri, version, kind, resultId)

JSONIFY(NotebookCell, kind, document, metadata, executionSummary)

JSONIFY(NotebookCellArrayChange, start, deleteCount, cells)

JSONIFY(ClientCapabilities, workspace, textDocument, notebookDocument, window, general, experimental)

JSONIFY(TextDocumentSyncOptions, openClose, change, willSave, willSaveWaitUntil, save)

JSONIFY(NotebookDocumentSyncOptions::NotebookSelectorType::CellsType, language)
JSONIFY(NotebookDocumentSyncOptions::NotebookSelectorType, notebook, cells)
JSONIFY(NotebookDocumentSyncOptions, notebookSelector, save)

JSONIFY(NotebookDocumentSyncRegistrationOptions, id, notebookSelector, save)

JSONIFY(WorkspaceFoldersServerCapabilities, supported, changeNotifications)

JSONIFY(FileOperationOptions, didCreate, willCreate, didRename, willRename, didDelete, willDelete)

JSONIFY(CodeDescription, href)

JSONIFY(DiagnosticRelatedInformation, location, message)

JSONIFY(ParameterInformation, label, documentation)

JSONIFY(NotebookCellTextDocumentFilter, notebook, language)

JSONIFY(FileOperationPatternOptions, ignoreCase)

JSONIFY(ExecutionSummary, executionOrder, success)

JSONIFY(WorkspaceClientCapabilities, applyEdit, workspaceEdit, didChangeConfiguration, didChangeWatchedFiles, symbol,
        executeCommand, workspaceFolders, configuration, semanticTokens, codeLens, fileOperations, inlineValue,
        inlayHint, diagnostics)

JSONIFY(TextDocumentClientCapabilities, synchronization, completion, hover, signatureHelp, declaration, definition,
        typeDefinition, implementation, references, documentHighlight, documentSymbol, codeAction, codeLens,
        documentLink, colorProvider, formatting, rangeFormatting, onTypeFormatting, rename, foldingRange,
        selectionRange, publishDiagnostics, callHierarchy, semanticTokens, linkedEditingRange, moniker, typeHierarchy,
        inlineValue, inlayHint, diagnostic)

JSONIFY(NotebookDocumentClientCapabilities, synchronization)

JSONIFY(WindowClientCapabilities, workDoneProgress, showMessage, showDocument)

JSONIFY(GeneralClientCapabilities::StaleRequestSupportType, cancel, retryOnContentModified)
JSONIFY(GeneralClientCapabilities, staleRequestSupport, regularExpressions, markdown, positionEncodings)

JSONIFY(RelativePattern, baseUri, pattern)

JSONIFY(WorkspaceEditClientCapabilities::ChangeAnnotationSupportType, groupsOnLabel)
JSONIFY(WorkspaceEditClientCapabilities, documentChanges, resourceOperations, failureHandling, normalizesLineEndings,
        changeAnnotationSupport)

JSONIFY(DidChangeConfigurationClientCapabilities, dynamicRegistration)

JSONIFY(DidChangeWatchedFilesClientCapabilities, dynamicRegistration, relativePatternSupport)

JSONIFY(WorkspaceSymbolClientCapabilities::SymbolKindType, valueSet)
JSONIFY(WorkspaceSymbolClientCapabilities::TagSupportType, valueSet)
JSONIFY(WorkspaceSymbolClientCapabilities::ResolveSupportType, properties)
JSONIFY(WorkspaceSymbolClientCapabilities, dynamicRegistration, symbolKind, tagSupport, resolveSupport)

JSONIFY(ExecuteCommandClientCapabilities, dynamicRegistration)

JSONIFY(SemanticTokensWorkspaceClientCapabilities, refreshSupport)

JSONIFY(CodeLensWorkspaceClientCapabilities, refreshSupport)

JSONIFY(FileOperationClientCapabilities, dynamicRegistration, didCreate, willCreate, didRename, willRename, didDelete,
        willDelete)

JSONIFY(InlineValueWorkspaceClientCapabilities, refreshSupport)

JSONIFY(InlayHintWorkspaceClientCapabilities, refreshSupport)

JSONIFY(DiagnosticWorkspaceClientCapabilities, refreshSupport)

JSONIFY(TextDocumentSyncClientCapabilities, dynamicRegistration, willSave, willSaveWaitUntil, didSave)

JSONIFY(CompletionClientCapabilities::CompletionItemType::TagSupportType, valueSet)
JSONIFY(CompletionClientCapabilities::CompletionItemType::ResolveSupportType, properties)
JSONIFY(CompletionClientCapabilities::CompletionItemType::InsertTextModeSupportType, valueSet)
JSONIFY(CompletionClientCapabilities::CompletionItemType, snippetSupport, commitCharactersSupport, documentationFormat,
        deprecatedSupport, preselectSupport, tagSupport, insertReplaceSupport, resolveSupport, insertTextModeSupport,
        labelDetailsSupport)
JSONIFY(CompletionClientCapabilities::CompletionItemKindType, valueSet)
JSONIFY(CompletionClientCapabilities::CompletionListType, itemDefaults)
JSONIFY(CompletionClientCapabilities, dynamicRegistration, completionItem, completionItemKind, insertTextMode,
        contextSupport, completionList)

JSONIFY(HoverClientCapabilities, dynamicRegistration, contentFormat)

JSONIFY(SignatureHelpClientCapabilities::SignatureInformationType::ParameterInformationType, labelOffsetSupport)
JSONIFY(SignatureHelpClientCapabilities::SignatureInformationType, documentationFormat, parameterInformation,
        activeParameterSupport)
JSONIFY(SignatureHelpClientCapabilities, dynamicRegistration, signatureInformation, contextSupport)

JSONIFY(DeclarationClientCapabilities, dynamicRegistration, linkSupport)

JSONIFY(DefinitionClientCapabilities, dynamicRegistration, linkSupport)

JSONIFY(TypeDefinitionClientCapabilities, dynamicRegistration, linkSupport)

JSONIFY(ImplementationClientCapabilities, dynamicRegistration, linkSupport)

JSONIFY(ReferenceClientCapabilities, dynamicRegistration)

JSONIFY(DocumentHighlightClientCapabilities, dynamicRegistration)

JSONIFY(DocumentSymbolClientCapabilities::SymbolKindType, valueSet)
JSONIFY(DocumentSymbolClientCapabilities::TagSupportType, valueSet)
JSONIFY(DocumentSymbolClientCapabilities, dynamicRegistration, symbolKind, hierarchicalDocumentSymbolSupport,
        tagSupport, labelSupport)

JSONIFY(CodeActionClientCapabilities::CodeActionLiteralSupportType::CodeActionKindType, valueSet)
JSONIFY(CodeActionClientCapabilities::CodeActionLiteralSupportType, codeActionKind)
JSONIFY(CodeActionClientCapabilities::ResolveSupportType, properties)
JSONIFY(CodeActionClientCapabilities, dynamicRegistration, codeActionLiteralSupport, isPreferredSupport,
        disabledSupport, dataSupport, resolveSupport, honorsChangeAnnotations)

JSONIFY(CodeLensClientCapabilities, dynamicRegistration)

JSONIFY(DocumentLinkClientCapabilities, dynamicRegistration, tooltipSupport)

JSONIFY(DocumentColorClientCapabilities, dynamicRegistration)

JSONIFY(DocumentFormattingClientCapabilities, dynamicRegistration)

JSONIFY(DocumentRangeFormattingClientCapabilities, dynamicRegistration)

JSONIFY(DocumentOnTypeFormattingClientCapabilities, dynamicRegistration)

JSONIFY(RenameClientCapabilities, dynamicRegistration, prepareSupport, prepareSupportDefaultBehavior,
        honorsChangeAnnotations)

JSONIFY(FoldingRangeClientCapabilities::FoldingRangeKindType, valueSet)
JSONIFY(FoldingRangeClientCapabilities::FoldingRangeType, collapsedText)
JSONIFY(FoldingRangeClientCapabilities, dynamicRegistration, rangeLimit, lineFoldingOnly, foldingRangeKind,
        foldingRange)

JSONIFY(SelectionRangeClientCapabilities, dynamicRegistration)

JSONIFY(PublishDiagnosticsClientCapabilities::TagSupportType, valueSet)
JSONIFY(PublishDiagnosticsClientCapabilities, relatedInformation, tagSupport, versionSupport, codeDescriptionSupport,
        dataSupport)

JSONIFY(CallHierarchyClientCapabilities, dynamicRegistration)

JSONIFY_EMPTY(SemanticTokensClientCapabilities::RequestsType::RangeType)
JSONIFY(SemanticTokensClientCapabilities::RequestsType::FullType, delta)
JSONIFY(SemanticTokensClientCapabilities::RequestsType, range, full)
JSONIFY(SemanticTokensClientCapabilities, dynamicRegistration, requests, tokenTypes, tokenModifiers, formats,
        overlappingTokenSupport, multilineTokenSupport, serverCancelSupport, augmentsSyntaxTokens)

JSONIFY(LinkedEditingRangeClientCapabilities, dynamicRegistration)

JSONIFY(MonikerClientCapabilities, dynamicRegistration)

JSONIFY(TypeHierarchyClientCapabilities, dynamicRegistration)

JSONIFY(InlineValueClientCapabilities, dynamicRegistration)

JSONIFY(InlayHintClientCapabilities::ResolveSupportType, properties)
JSONIFY(InlayHintClientCapabilities, dynamicRegistration, resolveSupport)

JSONIFY(DiagnosticClientCapabilities, dynamicRegistration, relatedDocumentSupport)

JSONIFY(NotebookDocumentSyncClientCapabilities, dynamicRegistration, executionSummarySupport)

JSONIFY(ShowMessageRequestClientCapabilities::MessageActionItemType, additionalPropertiesSupport)
JSONIFY(ShowMessageRequestClientCapabilities, messageActionItem)

JSONIFY(ShowDocumentClientCapabilities, support)

JSONIFY(RegularExpressionsClientCapabilities, engine, version)

JSONIFY(MarkdownClientCapabilities, parser, version, allowedTags)

JSONIFY(PrepareRenameResult_1, range, placeholder)

JSONIFY(PrepareRenameResult_2, defaultBehavior)

JSONIFY(TextDocumentContentChangeEventPartial, range, rangeLength, text)

JSONIFY(TextDocumentContentChangeEventFull, text)

JSONIFY(MarkedStringFull, language, value)

JSONIFY(TextDocumentFilter_1, language, scheme, pattern)

JSONIFY(TextDocumentFilter_2, language, scheme, pattern)

JSONIFY(TextDocumentFilter_3, language, scheme, pattern)

JSONIFY(NotebookDocumentFilter_1, notebookType, scheme, pattern)

JSONIFY(NotebookDocumentFilter_2, notebookType, scheme, pattern)

JSONIFY(NotebookDocumentFilter_3, notebookType, scheme, pattern)

}

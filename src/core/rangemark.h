#pragma once

#include <QObject>

#include <memory>

namespace Core {

class TextDocument;

// RangeMark is shared_ptr to a RangeMarkPrivate.
// This way we can ensure that a RangeMark is easy to copy and move
// around, whilst still ensuring the QObject that listens to the
// changes of the TextDocument is correctly deleted both from QML and C++.
class RangeMark
{
    Q_GADGET

    Q_PROPERTY(int start READ start FINAL)
    Q_PROPERTY(int end READ end FINAL)
    Q_PROPERTY(int length READ length FINAL)
    Q_PROPERTY(bool isValid READ isValid FINAL)
    Q_PROPERTY(QString text READ text FINAL)

public:
    // Default constructor is required for Q_DECLARE_METATYPE
    RangeMark() = default;

    explicit RangeMark(TextDocument *editor, int start, int end);

    bool isValid() const;

    int start() const;
    int end() const;
    int length() const;

    bool contains(int position) const;
    bool contains(const RangeMark &other) const;

    QString text() const;
    Q_INVOKABLE QString toString() const;

    TextDocument *document() const;

    // Text manipulation
    Q_INVOKABLE void select() const;
    Q_INVOKABLE void replace(const QString &text) const;

    // Interaction with other ranges
    Q_INVOKABLE RangeMark join(const RangeMark &other) const;

    bool operator==(const RangeMark &other) const;

private:
    std::shared_ptr<class RangeMarkPrivate> d = nullptr;

    friend TextDocument;
};

} // namespace Core
Q_DECLARE_METATYPE(Core::RangeMark)

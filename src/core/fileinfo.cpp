#include "fileinfo.h"

#include "logger.h"

#include <QFileInfo>

namespace Core {

/*!
 * \qmltype FileInfo
 * \brief Singleton with methods to handle file information.
 * \inqmlmodule Script
 * \ingroup Utilities
 * \since 1.0
 *
 * The `FileInfo` singleton implements most of the static methods from `QFileInfo`, check
 * [QFileInfo](https://doc.qt.io/qt-5/qfileinfo.html) documentation.
 */

FileInfo::FileInfo(QObject *parent)
    : QObject(parent)
{
}

FileInfo::~FileInfo() = default;

/*!
 * \qmlmethod bool FileInfo::exists(string file)
 */
bool FileInfo::exists(const QString &file)
{
    LOG("FileInfo::exists", file);
    return QFileInfo::exists(file);
}

/*!
 * \qmlmethod QFileInfoValueType FileInfo::create(string file)
 */
QFileInfoValueType FileInfo::create(const QString &file)
{
    LOG("FileInfo::create", file);
    return QFileInfoValueType(file);
}

} // namespace Core

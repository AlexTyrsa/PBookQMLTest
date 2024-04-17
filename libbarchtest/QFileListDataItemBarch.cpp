#include "QFileListDataItemBarch.h"

#include <QFileInfo>
#include <QDir>

QFileListDataItemBarch::QFileListDataItemBarch(int inID, const QString& inSrc, QObject *parent) : QFileListDataItem(inID, inSrc, parent)
{
    QFileInfo file(inSrc);
    QDir dir = file.absoluteDir();
    QString fileName = file.baseName();

    setDest(QFileInfo(dir, fileName + ".bmp").absoluteFilePath());
}

QString QFileListDataItemBarch::getPreview() const
{
    return getDestination();
}

void QFileListDataItemBarch::process()
{

}

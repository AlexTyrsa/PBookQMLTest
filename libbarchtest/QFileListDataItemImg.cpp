#include "QFileListDataItemImg.h"

#include <QFileInfo>
#include <QDir>

QFileListDataItemImg::QFileListDataItemImg(int inID, const QString& inSrc, QObject *parent) : QFileListDataItem(inID, inSrc, parent)
{
    QFileInfo file(inSrc);
    QDir dir = file.absoluteDir();
    QString fileName = file.baseName();

    setDest(QFileInfo(dir, fileName + ".barch").absoluteFilePath());
}

QString QFileListDataItemImg::getPreview() const
{
    return getSource();
}

void QFileListDataItemImg::process()
{

}

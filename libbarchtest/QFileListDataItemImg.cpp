#include "QFileListDataItemImg.h"

#include <QImage>
#include <QFileInfo>
#include <QDir>

QFileListDataItemImg::QFileListDataItemImg(int inID, const QString& inSrc, QObject *parent) : QFileListDataItem(inID, inSrc, parent)
{
    QFileInfo file(inSrc);
    QDir dir = file.absoluteDir();
    QString fileName = file.baseName();

    setDest(QFileInfo(dir, fileName + "_packed.barch").absoluteFilePath());
}

QString QFileListDataItemImg::getPreview() const
{
    return getSource();
}

void QFileListDataItemImg::process()
{
    setStatus(EQFileListDataItemStatus_InProgress);

    QImage image(getSource());

    if(image.isNull())
    {
        setStatusDescr("Fail to load image");
        setStatus(EQFileListDataItemStatus_Fail);
    }else if(image.format() != QImage::Format_Grayscale8)
    {
        setStatusDescr("unsupported format");
        setStatus(EQFileListDataItemStatus_Fail);
    }else
    {

    }



    setStatus(EQFileListDataItemStatus_Complete);
}

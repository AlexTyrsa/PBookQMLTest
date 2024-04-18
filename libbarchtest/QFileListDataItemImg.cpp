#include "QFileListDataItemImg.h"

#include "libbarch.h"

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

    QImage srcImage(getSource());

    if(srcImage.isNull())
    {
        setStatusDescr("Fail to load image");
        setStatus(EQFileListDataItemStatus_Fail);
    }else
    {
        if(srcImage.format() != QImage::Format_Grayscale8)
            srcImage.convertTo(QImage::Format_Grayscale8);

        std::vector<uint8_t> compressedData;

        try
        {
             compressedData = BarchCompressor(RawImageData(srcImage.width(), srcImage.height(), srcImage.bits())).Serialize();
        }catch(std::exception& e)
        {
            setStatusDescr(e.what());
            setStatus(EQFileListDataItemStatus_Fail);

            return;
        }

        QFile file(getDst());

        file.open(QIODeviceBase::ReadWrite);
        file.write(reinterpret_cast<char*>(compressedData.data()), compressedData.size());
        file.close();

        setDestSize(compressedData.size());

        setStatus(EQFileListDataItemStatus_Complete);
    }
}

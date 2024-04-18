#include "QFileListDataItemBarch.h"

#include "libbarch.h"

#include <QImage>
#include <QFileInfo>
#include <QDir>

QFileListDataItemBarch::QFileListDataItemBarch(int inID, const QString& inSrc, QObject *parent) : QFileListDataItem(inID, inSrc, parent)
{
    QFileInfo file(inSrc);
    QDir dir = file.absoluteDir();
    QString fileName = file.baseName();

    setDest(QFileInfo(dir, fileName + "unpacked.bmp").absoluteFilePath());
}

QString QFileListDataItemBarch::getPreview() const
{
    return getDestination();
}

void QFileListDataItemBarch::process()
{
    setStatus(EQFileListDataItemStatus_InProgress);

    QFile srcFile(getSource());

    srcFile.open(QIODeviceBase::ReadOnly);

    if(!srcFile.isOpen())
    {
        setStatusDescr("Fail to load image");
        setStatus(EQFileListDataItemStatus_Fail);
    }else
    {
        int chunk_size = 1024;
        QByteArray buffer;
        std::vector<uint8_t> compressedData;

        while (!srcFile.atEnd())
        {
            buffer = srcFile.read(chunk_size);
            compressedData.insert(compressedData.end(), buffer.cbegin(), buffer.cend());
        }

        srcFile.close();

        QImage dstImage;

        try
        {
            RawImageData imageData(std::move(BarchCompressor(compressedData).DeCompress()));

            dstImage = QImage(imageData.GetData().data(), imageData.GetWidth(), imageData.GetHeight(), QImage::Format_Grayscale8);
        }catch(std::exception& e)
        {
            setStatusDescr(e.what());
            setStatus(EQFileListDataItemStatus_Fail);

            return;
        }

        dstImage.save(getDst());
        setDestSize(dstImage.sizeInBytes());

        setStatus(EQFileListDataItemStatus_Complete);
    }
}

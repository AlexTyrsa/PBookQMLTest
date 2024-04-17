#include "QFileListDataItem.h"

#include <QThread>

QFileListDataItem::QFileListDataItem(int inID, const QString& inSrc, QObject *parent) : QFileListDataItemI(inID, inSrc, parent), mStatus(eQFileListDataItemStatus_Ready), mDstSize(0)
{

}

QString QFileListDataItem::getDestination() const
{
    if(getStatus() != eQFileListDataItemStatus_Complete)
        return QString();
    else
        return mDst;
}

qint64 QFileListDataItem::getDestinationSize() const
{
    return mDstSize;
}

int QFileListDataItem::getStatus() const
{
    return mStatus;
}

QString QFileListDataItem::getStatusDescription() const
{
    return mStatusDescr;
}

void QFileListDataItem::processItem()
{
    QThread* thread = QThread::create(&QFileListDataItem::process, this);

    QObject::connect(this, SIGNAL(destroyed(QObject)), thread, SLOT(terminate()));
}

void QFileListDataItem::setStatus(int inStatus)
{
    if(mStatus != inStatus)
    {
        mStatus = inStatus;

        emit statusChanged(getStatus());
    }
}

void QFileListDataItem::setDest(const QString &inDest)
{
    if(mDst != inDest)
    {
        mDst = inDest;

        emit destinationChanged(getDestination());
    }
}

void QFileListDataItem::setDestSize(qint64 inDstSize)
{
    if(mDstSize != inDstSize)
    {
        mDstSize = inDstSize;

        emit destinationSizeChanged(getDestinationSize());
    }
}

void QFileListDataItem::setStatusDescr(const QString &inSDescr)
{
    if(mStatusDescr != inSDescr)
    {
        mStatusDescr = inSDescr;

        emit statusDescriptionChanged(getStatusDescription());
    }
}

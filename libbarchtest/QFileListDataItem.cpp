#include "QFileListDataItem.h"

#include <QThread>

QFileListDataItem::QFileListDataItem(int inID, const QString& inSrc, QObject *parent) : QFileListDataItemI(inID, inSrc, parent), mStatus(eQFileListDataItemStatus_Ready)
{

}

QString QFileListDataItem::getDestination() const
{
    if(getStatus() != eQFileListDataItemStatus_Complete)
        return QString();
    else
        return mDst;
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

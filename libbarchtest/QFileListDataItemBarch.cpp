#include "QFileListDataItemBarch.h"

QFileListDataItemBarch::QFileListDataItemBarch(int inID, const QString& inSrc, QObject *parent) : QFileListDataItem(inID, inSrc, parent)
{

}

QString QFileListDataItemBarch::getPreview() const
{
    return getDestination();
}

void QFileListDataItemBarch::process()
{

}

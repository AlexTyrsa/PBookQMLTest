#include "QFileListDataItemI.h"

#include <QFileInfo>

QFileListDataItemI::QFileListDataItemI(int inID, const QString& inSrc, QObject *parent) : QObject(parent), mId(inID), mSrc(inSrc), mSrcSize(QFileInfo(inSrc).size())
{

}

int QFileListDataItemI::getId() const
{
    return mId;
}

QString QFileListDataItemI::getSource() const
{
    return mSrc;
}

qint64 QFileListDataItemI::getSourceSize() const
{
    return mSrcSize;
}

bool QFileListDataItemI::getSelected() const
{
    return mSelected;
}

void QFileListDataItemI::setSelected(bool inSelected)
{
    if(mSelected != inSelected)
    {
        mSelected = inSelected;

        emit selectedChanged(getSelected());
    }
}

void QFileListDataItemI::reqSetSelected(bool inSelected)
{
    emit requestSetSelected(getId(), inSelected);
}

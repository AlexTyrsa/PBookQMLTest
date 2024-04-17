#include "QFileListDataItemI.h"

QFileListDataItemI::QFileListDataItemI(int inID, const QString& inSrc, QObject *parent) : QObject(parent), mId(inID), mSrc(inSrc)
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

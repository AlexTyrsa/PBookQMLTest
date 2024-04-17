#include "QFileListDataItemImg.h"

QFileListDataItemImg::QFileListDataItemImg(int inID, const QString& inSrc, QObject *parent) : QFileListDataItem(inID, inSrc, parent)
{

}

QString QFileListDataItemImg::getPreview() const
{
    return getSource();
}

void QFileListDataItemImg::process()
{

}

#include "QFileListData.h"

#include "QFileListDataItemImg.h"
#include "QFileListDataItemBarch.h"

#include <QDir>

QFileListData::QFileListData(const QString &inPath, QObject *parent) : QObject(parent), mPath(inPath)
{
    dispatchFiles(inPath);
}

QString QFileListData::gePath() const
{
    return mPath;
}

QQmlListProperty<QFileListDataItemI> QFileListData::getItemsQML()
{
    return QQmlListProperty<QFileListDataItemI>(this, this, &QFileListData::itemsCount, &QFileListData::itemAt);
}

const QList<QFileListDataItemI*> &QFileListData::getItems() const
{
    return mItems;
}

void QFileListData::dispatchFiles(const QString &inDir)
{
    QDir dir(inDir);

    int id = 0;

    for (const QFileInfo &file : dir.entryInfoList({"*.png", "*.bmp", "*.barch"}, QDir::Files))
    {
        if(file.suffix() == "barch")
            mItems.push_back(new QFileListDataItemBarch(id, file.absoluteFilePath(), this));
        else
            mItems.push_back(new QFileListDataItemImg(id, file.absoluteFilePath(), this));

        ++id;
    }
}

qsizetype QFileListData::itemsCount(QQmlListProperty<QFileListDataItemI> *inProperty)
{
    return reinterpret_cast<QFileListData*>(inProperty->data)->getItems().count();
}

QFileListDataItemI *QFileListData::itemAt(QQmlListProperty<QFileListDataItemI> *inProperty, qsizetype inIndex)
{
    return reinterpret_cast<QFileListData*>(inProperty->data)->getItems().at(inIndex);
}



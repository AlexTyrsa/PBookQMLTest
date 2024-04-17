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

QFileListDataItemI *QFileListData::getSelected() const
{
    for(QFileListDataItemI* item : mItems)
    {
        if(item && item->getSelected())
            return item;
    }

    return nullptr;
}

void QFileListData::dispatchFiles(const QString &inDir)
{
    QDir dir(inDir);

    int id = 0;

    for (const QFileInfo &file : dir.entryInfoList({"*.png", "*.bmp", "*.barch"}, QDir::Files))
    {
        QFileListDataItemI* item = nullptr;

        if(file.suffix() == "barch")
            item = new QFileListDataItemBarch(id, file.absoluteFilePath(), this);
        else
            item = new QFileListDataItemImg(id, file.absoluteFilePath(), this);

        mItems.push_back(item);

        QObject::connect(item, SIGNAL(requestSetSelected(int,bool)), this, SLOT(onRequestSetSelected(int,bool)));

        ++id;
    }
}

void QFileListData::onRequestSetSelected(int inId, bool inSelected)
{
    QFileListDataItemI* selectedItem = nullptr;

    for(QFileListDataItemI* item : mItems)
    {
        if(item && item->getId() == inId)
        {
            item->setSelected(true);

            selectedItem = item;
        }
        else
        {
            item->setSelected(false);
        }
    }

    emit selectedChanged(selectedItem);
}

qsizetype QFileListData::itemsCount(QQmlListProperty<QFileListDataItemI> *inProperty)
{
    return reinterpret_cast<QFileListData*>(inProperty->data)->getItems().count();
}

QFileListDataItemI *QFileListData::itemAt(QQmlListProperty<QFileListDataItemI> *inProperty, qsizetype inIndex)
{
    return reinterpret_cast<QFileListData*>(inProperty->data)->getItems().at(inIndex);
}



#pragma once

#include <QObject>
#include <QQmlListProperty>

#include "QFileListDataItemI.h"

class QFileListData : public QObject
{
    Q_OBJECT

public:
    Q_PROPERTY(QString path READ gePath CONSTANT)
    Q_PROPERTY(QQmlListProperty<QFileListDataItemI> items READ getItemsQML CONSTANT)

public:
    QFileListData(const QString& inPath, QObject* parent = nullptr);

    QString gePath() const;

    QQmlListProperty<QFileListDataItemI> getItemsQML();
    const QList<QFileListDataItemI*>& getItems() const;

private:
    void dispatchFiles(const QString& inDir);

private:
    static qsizetype itemsCount(QQmlListProperty<QFileListDataItemI>* inProperty);
    static QFileListDataItemI* itemAt(QQmlListProperty<QFileListDataItemI>* inProperty, qsizetype inIndex);

private:
    QString mPath;
    QList<QFileListDataItemI*> mItems;

};

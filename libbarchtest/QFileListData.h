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
    Q_PROPERTY(QFileListDataItemI* selected READ getSelected NOTIFY selectedChanged)

public:
    QFileListData(const QString& inPath = "", QObject* parent = nullptr);

    QString gePath() const;

    QQmlListProperty<QFileListDataItemI> getItemsQML();
    const QList<QFileListDataItemI*>& getItems() const;

    QFileListDataItemI* getSelected() const;

signals:
    void selectedChanged(QFileListDataItemI*);

private:
    void dispatchFiles(const QString& inDir);

private slots:
    void onRequestSetSelected(int inId, bool inSelected);

private:
    static qsizetype itemsCount(QQmlListProperty<QFileListDataItemI>* inProperty);
    static QFileListDataItemI* itemAt(QQmlListProperty<QFileListDataItemI>* inProperty, qsizetype inIndex);

private:
    QString mPath;
    QList<QFileListDataItemI*> mItems;

};

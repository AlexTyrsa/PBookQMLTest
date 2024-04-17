#pragma once

#include "QFileListDataItemI.h"

class QFileListDataItem : public QFileListDataItemI
{
    Q_OBJECT

public:
    QFileListDataItem(int inID, const QString& inSrc, QObject* parent = nullptr);

    QString getDestination() const override;

    int getStatus() const override;
    QString getStatusDescription() const override;

public slots:
    Q_INVOKABLE void processItem() override;

protected:
    virtual void process() = 0;

protected:
    int mStatus;
    QString mDst;
    QString mStatusDescr;

};

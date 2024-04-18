#pragma once

#include "QFileListDataItemI.h"

class QFileListDataItem : public QFileListDataItemI
{
    Q_OBJECT

public:
    QFileListDataItem(int inID, const QString& inSrc, QObject* parent = nullptr);

    QString getDestination() const override;
    qint64 getDestinationSize() const override;

    int getStatus() const override;
    QString getStatusDescription() const override;

public slots:
    Q_INVOKABLE void processItem() override;

protected:
    virtual void process() = 0;

    void setStatus(int inStatus);
    void setDest(const QString& inDest);
    void setDestSize(qint64 inDstSize);
    void setStatusDescr(const QString& inSDescr);

    QString getDst() const;

private:
    int mStatus;
    QString mDst;
    QString mStatusDescr;
    qint64  mDstSize;

};

#pragma once

#include "QFileListDataItem.h"

class QFileListDataItemBarch : public QFileListDataItem
{
    Q_OBJECT

public:
    QFileListDataItemBarch(int inID, const QString& inSrc, QObject* parent = nullptr);

    QString getPreview() const override;

protected:
    void process() override;

};

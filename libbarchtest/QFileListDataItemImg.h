#pragma once

#include "QFileListDataItem.h"

class QFileListDataItemImg : public QFileListDataItem
{
    Q_OBJECT

public:
    QFileListDataItemImg(int inID, const QString& inSrc, QObject* parent = nullptr);

    QString getPreview() const override;

protected:
    void process() override;

};

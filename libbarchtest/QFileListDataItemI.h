#pragma once

#include <QObject>

class QFileListDataItemI : public QObject
{
    Q_OBJECT

public:
    Q_PROPERTY(int id READ getId CONSTANT)

    Q_PROPERTY(QString source READ getSource CONSTANT)
    Q_PROPERTY(QString destination READ getDestination NOTIFY destinationChanged)

    Q_PROPERTY(int status READ getStatus NOTIFY statusChanged)
    Q_PROPERTY(QString statusDescription READ getStatusDescription NOTIFY statusDescriptionChanged)

    Q_PROPERTY(QString preview READ getPreview NOTIFY previewChanged)

public:
    enum EQFileListDataItemStatus
    {
        eQFileListDataItemStatus_Ready,
        eQFileListDataItemStatus_InProgress,
        eQFileListDataItemStatus_Complete,
        eQFileListDataItemStatus_Fail
    };

public:
    QFileListDataItemI(int inID, const QString& inSrc, QObject* parent = nullptr);

    int getId() const;

    QString getSource() const;
    virtual QString getDestination() const = 0;

    virtual int getStatus() const = 0;
    virtual QString getStatusDescription() const = 0;

    virtual QString getPreview() const = 0;

public slots:
    Q_INVOKABLE virtual void processItem() = 0;

signals:
    void destinationChanged(QString);
    void statusChanged(int);
    void statusDescriptionChanged(QString);
    void previewChanged(QString);

private:
    int mId;
    QString mSrc;

};

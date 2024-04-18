#pragma once

#include <QObject>

class QFileListDataItemI : public QObject
{
    Q_OBJECT

public:
    Q_PROPERTY(int id READ getId CONSTANT)

    Q_PROPERTY(QString source READ getSource CONSTANT)
    Q_PROPERTY(QString destination READ getDestination NOTIFY destinationChanged)

    Q_PROPERTY(qint64 sourceSize READ getSourceSize CONSTANT)
    Q_PROPERTY(qint64 destinationSize READ getDestinationSize NOTIFY destinationSizeChanged)

    Q_PROPERTY(int status READ getStatus NOTIFY statusChanged)
    Q_PROPERTY(QString statusDescription READ getStatusDescription NOTIFY statusDescriptionChanged)

    Q_PROPERTY(QString preview READ getPreview NOTIFY previewChanged)

    Q_PROPERTY(bool selected READ getSelected WRITE reqSetSelected NOTIFY selectedChanged)

public:
    enum EQFileListDataItemStatus
    {
        EQFileListDataItemStatus_Ready,
        EQFileListDataItemStatus_InProgress,
        EQFileListDataItemStatus_Complete,
        EQFileListDataItemStatus_Fail
    };

    Q_ENUM(EQFileListDataItemStatus)

public:
    QFileListDataItemI(int inID, const QString& inSrc, QObject* parent = nullptr);

    int getId() const;

    QString getSource() const;
    qint64 getSourceSize() const;

    bool getSelected() const;
    void setSelected(bool inSelected);
    void reqSetSelected(bool inSelected);

    virtual QString getDestination() const = 0;
    virtual qint64 getDestinationSize() const = 0;

    virtual int getStatus() const = 0;
    virtual QString getStatusDescription() const = 0;

    virtual QString getPreview() const = 0;

public slots:
    Q_INVOKABLE virtual void processItem() = 0;

signals:
    void destinationChanged(QString);
    void destinationSizeChanged(qint64);
    void statusChanged(int);
    void statusDescriptionChanged(QString);
    void previewChanged(QString);
    void selectedChanged(bool);
    void requestSetSelected(int, bool);

private:
    int mId;
    QString mSrc;
    qint64 mSrcSize;
    bool mSelected;

};

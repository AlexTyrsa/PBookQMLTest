#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <QStandardPaths>
#include <QDir>

#include "QFileListData.h"
#include "QFileListDataItemI.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    qmlRegisterType<QFileListData>("QFileListLib", 1, 0, "QFileListData");
    qmlRegisterUncreatableType<QFileListDataItemI>("QFileListLib", 1, 0, "QFileListDataItemI", "Interface");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, [url](QObject *obj, const QUrl &objUrl)
    {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    QObject* rootObj = engine.rootObjects().at(0);
    QObject* viewObj = rootObj->findChild<QQuickItem*>("fileView");

    if(viewObj)
    {
        QString defaultPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

        if(QCoreApplication::arguments().length() > 1)
        {
            QString argPath = QCoreApplication::arguments().at(1);

            if(QDir(argPath).exists())
                defaultPath = argPath;
        }

        viewObj->setProperty("dataList", QVariant::fromValue(new QFileListData(defaultPath)));
    }

    return app.exec();
}

#include <QtQml>
#include <QQuickView>
#include <QGuiApplication>
#include <QObject>
#include "mdevice.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlEngine engine;
    QObject::connect(&engine, &QQmlEngine::quit, &app, &QGuiApplication::quit);

    MDevice m_device;
    engine.rootContext()->setContextProperty("device", &m_device);

    QQmlComponent component(&engine, QUrl("qrc:///qml/GControl/main.qml"));
    QObject *topLevel = component.create();
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);

    QSurfaceFormat surfaceFormat = window->requestedFormat();
    window->setFormat(surfaceFormat);
    window->showMaximized();

    m_device.setCertificate("../../GServer/keys/client.pem");
    m_device.createConnection("zloy-dev", 32345);

    return app.exec();
}

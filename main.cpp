#include <QGuiApplication>
#include <QApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include <QList>
#include <QString>

#include "serialinterface.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    SerialInterface serial_interface;

    engine.rootContext()->setContextProperty("serial",&serial_interface);


    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("FeMauApp", "Main");

    return app.exec();
}

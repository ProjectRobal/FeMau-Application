#include <QGuiApplication>
#include <QApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include <QList>
#include <QString>
#include <QLineSeries>

#include <QDebug>

#include "serialinterface.h"
#include "console.h"
#include "chart.h"

#include "pid.h"

#include "common.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // qmlRegisterUncreatableType<PID>("qml.pid", 1, 0, "PID","");

    qmlRegisterUncreatableType<PID>("qml.pid", 1, 0, "pid","");

    SerialInterface serial_interface;
    Console console;
    Chart chart;
    Common common;

    QObject::connect(&serial_interface,SIGNAL(gotByte(char)),&console,SLOT(process(char)));
    // recive Hello message
    QObject::connect(&console,SIGNAL(got_hello_message()),&serial_interface,SLOT(onHelloMSG()));

    engine.rootContext()->setContextProperty("serial",&serial_interface);
    engine.rootContext()->setContextProperty("term",&console);
    engine.rootContext()->setContextProperty("common",&common);
    engine.rootContext()->setContextProperty("chart_tool",&chart);



    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("FeMauApp", "Main");

    serial_interface.scan_for_serial();

    return app.exec();
}

#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QQmlEngine>

#include <pid.h>

#define BUFFER_SIZE 64

class Console : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    char header[64];
    char value[64];

    bool extract_header;

    size_t message_iter;

public:
    explicit Console(QObject *parent = nullptr);

    void process_message();


public slots:
    void process(char byte);

signals:

    void got_hello_message();

    void got_current_temperature(float temperature);

    void got_target_temperature(float temperature);

    void got_power(float power);

    void got_pid(PID pid);

    void got_mode(bool automatic);

    void got_heater_status(bool status);

    void got_wrong_message();
};

#endif // CONSOLE_H

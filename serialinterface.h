#ifndef SERIALINTERFACE_H
#define SERIALINTERFACE_H

#include <QObject>
#include <QQmlEngine>
#include <QThread>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QList>
#include <QString>

#include <QDebug>

#include "pid.h"

class SerialInterface : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    QList<QString> serial_devices;

    size_t device_index;

    QSerialPort serial;

    bool connected;

    bool checkDisconnected()
    {
        return ! this->connected;
    }

    bool checkConnected()
    {
        return this->connected;
    }

    void send_int(const char* header,int32_t value);

public:
    explicit SerialInterface(QObject *parent = nullptr);


public slots:

    void set_pid(PID pid);

    void scan_for_serial();

    void connect_to_serial();

    void serial_selected(size_t device_index);

    void serial_data_ready();

    void set_temperature(float temperature);

    void set_power(float power);

    void on_serial_error(QSerialPort::SerialPortError error)
    {
        if( error == QSerialPort::SerialPortError::NoError )
        {
            return;
        }

        this->emitDisconnected();
        this->connected = false;

        qDebug()<<"Serial error ocurred"<<error;
    }

    void emitConnected()
    {
        emit this->serialConnected();
    }

    void emitDisconnected()
    {
        emit this->serialDisconnected();
    }

    void onHelloMSG()
    {
        qDebug()<<"Got Hello message, devide is ready";
        this->connected = true;
        emit this->emitConnected();

        // get current mode
        this->serial.write("MG:\n");
        QThread::msleep(500);
        this->serial.write("PIDG:\n");
        QThread::msleep(500);
        this->serial.write("HSS:\n");
    }

signals:

    void serialConnected();

    void serialDisconnected();

    void updateList(const QList<QString>& dev_list);

    void gotByte(char byte);
};

#endif // SERIALINTERFACE_H

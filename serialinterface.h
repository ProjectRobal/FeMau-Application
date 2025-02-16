#ifndef SERIALINTERFACE_H
#define SERIALINTERFACE_H

#include <QObject>
#include <QQmlEngine>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QList>
#include <QString>

#include <QDebug>


class SerialInterface : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    QList<QString> serial_devices;

    size_t device_index;

    QSerialPort serial;

    bool connected;

public:
    explicit SerialInterface(QObject *parent = nullptr);


public slots:

    void scan_for_serial();

    void connect_to_serial();

    void serial_selected(size_t device_index);

    void serial_data_ready();

    void on_serial_error(QSerialPort::SerialPortError error)
    {
        if( error == QSerialPort::SerialPortError::NoError )
        {
            return;
        }

        this->emitDisconnected();

        qDebug()<<"Serial error ocurred"<<error;
    }

    void emitConnected()
    {
        emit this->serialConnected();
    }

    void emitDisconnected()
    {
        emit this->serialDisconcted();
    }

signals:

    void serialConnected();

    void serialDisconcted();

    void updateList(const QList<QString>& dev_list);
};

#endif // SERIALINTERFACE_H

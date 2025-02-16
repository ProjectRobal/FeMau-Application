#ifndef SERIALINTERFACE_H
#define SERIALINTERFACE_H

#include <QObject>
#include <QQmlEngine>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QList>
#include <QString>

class SerialInterface : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    QList<QString> serial_devices;

    size_t device_index;

public:
    explicit SerialInterface(QObject *parent = nullptr);


public slots:

    void scan_for_serial();

signals:

    void serialConnected();

    void serialDisconcted();

    void updateList(const QList<QString>& dev_list);
};

#endif // SERIALINTERFACE_H

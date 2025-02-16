#include "serialinterface.h"

#include <QtSerialPort/QSerialPortInfo>

SerialInterface::SerialInterface(QObject *parent)
    : QObject{parent}
{
    this->device_index = 0;

    this->connected = false;

    QObject::connect(&this->serial,SIGNAL(errorOccurred(QSerialPort::SerialPortError)),this,SLOT(on_serial_error(QSerialPort::SerialPortError)));

    QObject::connect(&this->serial,SIGNAL(readyRead()),this,SLOT(serial_data_ready()));
}

void SerialInterface::scan_for_serial()
{
    this->serial_devices.clear();

    const auto avaliablePorts = QSerialPortInfo::availablePorts();

    for( const QSerialPortInfo& info : avaliablePorts )
    {
        this->serial_devices.push_back(info.systemLocation());
    }

    this->device_index = 0;

    emit this->updateList(this->serial_devices);
}

void SerialInterface::connect_to_serial()
{
    if( this->device_index > this->serial_devices.size() )
    {
        return;
    }

    this->serial.setPortName(this->serial_devices[this->device_index]);

    if( this->serial.open(QIODeviceBase::ReadWrite) )
    {
        emit this->serialConnected();
        // send welcome messages to device

        this->serial.write("HI:\n");

    }
    else
    {
        emit this->serialDisconcted();
    }
}

void SerialInterface::serial_selected(size_t device_index)
{
    this->device_index = device_index;
}

void SerialInterface::serial_data_ready()
{
    char byte;


    while(this->serial.getChar(&byte))
    {
        // put byte to process
    }

}

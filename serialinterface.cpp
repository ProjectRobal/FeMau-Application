#include "serialinterface.h"

#include <QtSerialPort/QSerialPortInfo>

SerialInterface::SerialInterface(QObject *parent)
    : QObject{parent}
{
    this->device_index = 0;
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

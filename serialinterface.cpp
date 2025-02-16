#include "serialinterface.h"

#include <string>
#include <sstream>

#include <QtSerialPort/QSerialPortInfo>

void SerialInterface::send_int(const char* header,int32_t value)
{
    const std::string str = std::to_string(value);

    const char* buffer = str.c_str();

    if( buffer == nullptr )
    {
        return;
    }

    this->serial.write(header);
    this->serial.putChar(':');
    this->serial.write(buffer);
    this->serial.putChar('\n');
}

SerialInterface::SerialInterface(QObject *parent)
    : QObject{parent}
{
    this->device_index = 0;

    this->connected = false;

    QObject::connect(&this->serial,SIGNAL(errorOccurred(QSerialPort::SerialPortError)),this,SLOT(on_serial_error(QSerialPort::SerialPortError)));

    QObject::connect(&this->serial,SIGNAL(readyRead()),this,SLOT(serial_data_ready()));

}

void SerialInterface::set_pid(PID pid)
{
    if( this->checkDisconnected() )
    {
        return;
    }

    const char* header = "PID:";

    int32_t p = pid.P();
    int32_t i = pid.I();
    int32_t d = pid.D();

    qDebug()<<"Sending PID: "<<p<<","<<i<<","<<d;

    std::string str;

    std::ostringstream ss_buff(str);

    ss_buff<<p<<','<<i<<','<<d<<'\n';

    const char* buffer = str.c_str();

    this->serial.write(header);
    this->serial.write(buffer);
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
        emit this->serialDisconnected();
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
        emit this->gotByte(byte);
    }

}

void SerialInterface::set_temperature(float temperature)
{
    if( this->checkDisconnected() )
    {
        return;
    }

    qDebug()<<"Setting temperature: "<<temperature;

    int32_t raw = static_cast<int32_t>(temperature*100.f);

    this->send_int("TS",raw);
}

void SerialInterface::set_power(float power)
{
    if( this->checkDisconnected() )
    {
        return;
    }

    qDebug()<<"Setting power: "<<power<<" %";

    int32_t raw = static_cast<int32_t>( (power/100.f)*4095.f );

    this->send_int("PS",raw);
}

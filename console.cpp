#include "console.h"

#include <cstdlib>

#include <memory.h>

static bool compare(const char* s1,const char* s2)
{
    return strncmp(s1,s1,BUFFER_SIZE) == 0;
}

Console::Console(QObject *parent)
    : QObject{parent}
{
    this->extract_header = true;
    this->message_iter = 0;
}

void Console::process(char byte)
{
    if( message_iter == 0 )
    {
        if( extract_header )
        {
            memset(header,0,BUFFER_SIZE);
        }
        else
        {
            memset(value,0,BUFFER_SIZE);
        }
    }

    if( extract_header )
    {
        // igonore white letters
        if( byte < 32 || byte > 126 )
        {
            return;
        }

        if( byte == ':' )
        {
            extract_header = false;
            message_iter = 0;
            return;
        }

        header[message_iter++] = byte;
    }
    else
    {
        if( byte == '\n' || byte == '\r' )
        {
            extract_header = true;
            message_iter = 0;
            this->process_message();
            return;
        }
        value[message_iter++] = byte;
    }

    if( message_iter >= BUFFER_SIZE-1 )
    {
        message_iter = 0;

        if( extract_header )
        {
            memset(header,0,BUFFER_SIZE);
        }
        else
        {
            memset(value,0,BUFFER_SIZE);
        }
    }

}

void Console::process_message()
{
    if( compare(header,"HELLO") )
    {
        emit this->got_hello_message();
    }
    else if( compare(header,"PID") )
    {
        PID pid;

        // P, I , D
        int32_t params[3] = {0};

        char buffer[255] = {0};

        uint16_t iterator = 0;

        uint16_t buffer_iter = 0;

        const uint32_t value_len = strlen(value);

        for(uint8_t i=0;i<3;i++)
        {
            while( value[iterator] != ',' && value[iterator] != 0 && iterator <= value_len )
            {
                buffer[buffer_iter++] = value[iterator++];
            }

            if( iterator > value_len )
            {
                return;
            }

            params[i] = atoi(buffer);

            buffer_iter = 0;
            memset(buffer,0,255);

            // avoid ',' character
            iterator++;
        }

        if( params[0] == 0 )
        {
            return;
        }

        pid.setP(params[0]);
        pid.setI(params[1]);
        pid.setD(params[2]);

        emit this->got_pid(pid);

    }
    else if( compare(header,"M") )
    {
        bool mode =  value[0] == '1';

        emit this->got_mode(mode);
    }
    else if( compare(header,"HS") )
    {
        bool status =  value[0] == '1';

        emit this->got_heater_status(status);
    }
    else if( compare(header,"TC") )
    {
        uint32_t raw = std::atoi(value);

        float temperature = static_cast<float>(raw)/100.f;

        emit this->got_current_temperature(temperature);
    }
    else if( compare(header,"TA") )
    {
        uint32_t raw = std::atoi(value);

        float temperature = static_cast<float>(raw)/100.f;

        emit this->got_target_temperature(temperature);
    }
    else if( compare(header,"PW") )
    {
        uint32_t raw = std::atoi(value);

        float power = ( static_cast<float>(raw)/4095.f )*100.f;

        emit this->got_power(power);
    }
    else if( compare(header,"NOK") )
    {
        emit this->got_wrong_message();
    }

}

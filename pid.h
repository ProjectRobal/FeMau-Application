#ifndef PID_H
#define PID_H

#include <QObject>
#include <QMetaType>
#include <qqml.h>

class PID
{

    float p;
    float i;
    float d;

    Q_GADGET
    Q_PROPERTY(float p READ P WRITE setP)
    Q_PROPERTY(float i READ I WRITE setI)
    Q_PROPERTY(float d READ D WRITE setD)

public:

    PID()
    {}

    PID(float p,float i,float d)
    {
        this->p = p;
        this->i = i;
        this->d = d;
    }

    float P()
    {
        return this->p;
    }

    float I()
    {
        return this->i;
    }

    float D()
    {
        return this->d;
    }

    void setP(float p)
    {
        this->p = p;
    }

    void setI(float i)
    {
        this->i = i;
    }

    void setD(float d)
    {
        this->d = d;
    }

};

Q_DECLARE_METATYPE(PID);

#endif // PID_H

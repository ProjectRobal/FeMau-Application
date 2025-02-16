#ifndef COMMON_H
#define COMMON_H

#include <QObject>
#include <QQmlEngine>

#include "pid.h"

class Common : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    PID pid;

    Q_PROPERTY(PID pid READ getPID WRITE setPID NOTIFY PIDChanged)

public:
    explicit Common(QObject *parent = nullptr);

    PID getPID()
    {
        return this->pid;
    }

public slots:

    void setPID(const PID& pid)
    {
        this->pid = pid;
        emit this->PIDChanged();
    }

signals:

    void PIDChanged();
};

#endif // COMMON_H

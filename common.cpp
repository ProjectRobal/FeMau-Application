#include "common.h"

Common::Common(QObject *parent)
    : QObject{parent}
{
    this->pid = PID(1000,0,0);
}

#include "chart.h"

#include <QFile>
#include <QString>
#include <QTextStream>

Chart::Chart(QObject *parent)
    : QObject{parent}
{}

void Chart::saveToFile(const QString& text, const QString &fileName)
{
    QFile file(fileName);

    if( !file.open(QIODevice::WriteOnly) )
    {
        emit this->fileError();
        return;
    }

    QTextStream stream(&file);

    //stream<<"N,Time [ms],Temperature [°C]\n";

    stream<<text;

    file.close();
}

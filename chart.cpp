#include "chart.h"

#include <QFile>
#include <QString>
#include <QTextStream>

Chart::Chart(QObject *parent)
    : QObject{parent}
{}

void Chart::saveToFile(const QLineSeries &series, const QString &fileName)
{
    QFile file(fileName);

    if( !file.open(QIODevice::WriteOnly|QIODevice::Text) )
    {
        emit this->fileError();
        return;
    }

    QTextStream stream(&file);

    stream<<"N,Time [ms],Temperature [°C]\n";

    for( size_t i=0; i<series.count(); i++ )
    {
        const QPointF& point = series.at(i);

        QString line;

        stream<<i<<","<<point.x()<<","<<point.y()<<'\n';
    }

    file.close();
}

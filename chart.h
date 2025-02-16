#ifndef CHART_H
#define CHART_H

#include <QObject>
#include <QQmlEngine>

#include <QLineSeries>
#include <QString>

class Chart : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit Chart(QObject *parent = nullptr);

public slots:

    void saveToFile(const QLineSeries& series,const QString& fileName);

signals:

    void fileError();
};

#endif // CHART_H

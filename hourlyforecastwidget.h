#ifndef HOURLYFORECASTWIDGET_H
#define HOURLYFORECASTWIDGET_H

#include "weatherwidget.h"
#include <QObject>
#include <QWidget>

class HourlyForecastWidget : public WeatherWidget<HourlyForecastLine>
{
    Q_OBJECT
public:
    HourlyForecastWidget(QWidget *parent = nullptr) : WeatherWidget<HourlyForecastLine>(parent){};
    void setup(Weather& weather);
public slots:
    void updateHourlyForecast(int dayIndex);
private:
    void fillCurrentHourlyForecast();
};

#endif // HOURLYFORECASTWIDGET_H

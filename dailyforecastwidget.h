#ifndef DAILYFORECASTWIDGET_H
#define DAILYFORECASTWIDGET_H

#include "weatherwidget.h"

class DailyForecastWidget : public WeatherWidget<DailyForecastLine>
{
    Q_OBJECT
public:
    DailyForecastWidget(QWidget *parent = nullptr) : WeatherWidget<DailyForecastLine>(parent){};
    void setup(Weather& weather);
private:
    void fillDailyForecast();
};

#endif // DAILYFORECASTWIDGET_H

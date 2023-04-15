#ifndef DAILYFORECASTWIDGET_H
#define DAILYFORECASTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMainWindow>
#include <QRegion>
#include "dailyforecastscrollarea.h"

class DailyForecastWidget : public QWidget
{
public:
    DailyForecastWidget(QWidget* parent = nullptr);
    void setBackground(QString path);
    void setForecast(Weather& weather);
private:
    QLabel* background;
    DailyForecastScrollArea* forecastScrollArea;
    QSize widgetSize;
};

#endif // DAILYFORECASTWIDGET_H

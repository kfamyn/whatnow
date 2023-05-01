#ifndef SMOOTHSCROLLAREAWIDGET_H
#define SMOOTHSCROLLAREAWIDGET_H

#include "smoothscrollarea.h"
#include "hourlyforecastline.h"
#include "weatherAPI.h"
#include "DailyForecastLine.h"
#include <QLabel>

class SmoothScrollAreaWidget : public QWidget
{
    Q_OBJECT
public:
    enum contents {DAILYFORECAST = 0, HOURLYFORECAST = 1, NEWS = 2};
    SmoothScrollAreaWidget(QWidget* parent);
    void setup(Weather& weather, contents typeOfContents );
    void setBackground(QString path, QSize size);
    HourlyForecastLine* getHourlyForecastLine(int index);
    DailyForecastLine* getDailyForecastLine(int index);
public slots:
    void setHourlyForecast(int dayIndex);
private:
    Weather* weather;
    QLabel* background;
    HourlyForecastLine* hourlyForecastLines[24];
    DailyForecastLine* dailyForecastLines[14];
    SmoothScrollArea* widgetScrollarea;
    QWidget* scrollAreaWidgetContents;
    void setupDailyForecast(Weather& weather);
    void setupHourlyForecast(Weather& weather);

    void setupDailyForecastLines(Weather& weather);
};

#endif // SMOOTHSCROLLAREAWIDGET_H

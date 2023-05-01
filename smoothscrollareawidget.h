#ifndef SMOOTHSCROLLAREAWIDGET_H
#define SMOOTHSCROLLAREAWIDGET_H

#include "smoothscrollarea.h"
#include "hourlyforecastline.h"
#include "weatherAPI.h"
#include "dailyforecastline.h"
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
    QWidget* getWidgetContents();
public slots:
    void updateHourlyForecast(int dayIndex);
private:
    Weather* weather;
    QLabel* background;
    HourlyForecastLine* hourlyForecastLines[24];
    DailyForecastLine* dailyForecastLines[14];
    SmoothScrollArea* widgetScrollarea;
    QWidget* scrollAreaWidgetContents;
    void setupDailyForecast();
    void setupHourlyForecast();
    void fillCurrentHourlyForecast();
    void fillDailyForecast();
};

#endif // SMOOTHSCROLLAREAWIDGET_H

#ifndef SMOOTHSCROLLAREAWIDGET_H
#define SMOOTHSCROLLAREAWIDGET_H

#include "smoothscrollarea.h"
#include "weatherAPI.h"
#include <QLabel>

class SmoothScrollAreaWidget : public QWidget
{
    Q_OBJECT
public:
    enum contents {DAILYFORECAST = 0, HOURLYFORECAST = 1, NEWS = 2};
    SmoothScrollAreaWidget(QWidget* parent);
    void setup(Weather& weather, contents typeOfContents );
    void setBackground(QString path, QSize size);
private:
    SmoothScrollArea* widgetScrollarea;
    QWidget* scrollAreaWidgetContents;
    QLabel* background;

    void setupDailyForecast(Weather& weather);
    void setupHourlyForecast(Weather& weather);

    void setupDailyForecastLines(Weather& weather);
};

#endif // SMOOTHSCROLLAREAWIDGET_H

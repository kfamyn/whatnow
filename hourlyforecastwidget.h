#ifndef HOURLYFORECASTWIDGET_H
#define HOURLYFORECASTWIDGET_H

#include "smoothscrollarea.h"
#include "hourlyforecastline.h"
#ifndef WEATHERAPIH
#define WEATHERAPIH
#include "weatherAPI.h"
#endif


class HourlyForecastWidget : public QWidget
{
    Q_OBJECT
public:
    HourlyForecastWidget(QWidget* parent);
    void setup(Weather& weather);
    void setBackground(QString path);
private:
    SmoothScrollArea* widgetScrollarea;
    QWidget* scrollAreaWidgetContents;
    QLabel* background;
};

#endif // HOURLYFORECASTWIDGET_H

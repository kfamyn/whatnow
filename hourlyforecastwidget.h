#ifndef HOURLYFORECASTWIDGET_H
#define HOURLYFORECASTWIDGET_H

#include "smoothscrollarea.h"
#include "hourlyforecastline.h"
#include "weatherAPI.h"
#include "format.hpp"

class HourlyForecastWidget : public QWidget
{
    Q_OBJECT
public:
    HourlyForecastWidget(QWidget* parent);
    void setup(Weather& weather);
    void setBackground(QString path, QSize size);
private:
    SmoothScrollArea* widgetScrollarea;
    QWidget* scrollAreaWidgetContents;
    QLabel* background;
};

#endif // HOURLYFORECASTWIDGET_H

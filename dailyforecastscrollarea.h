#ifndef DAILYFORECASTSCROLLAREA_H
#define DAILYFORECASTSCROLLAREA_H

#include <QObject>
#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QCommonStyle>
#include <QScrollBar>
#include <QEvent>
#include <QWheelEvent>
#include <QPropertyAnimation>
#include <QScrollBar>
#include "weatherAPI.h"

class DailyForecastScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    DailyForecastScrollArea(QWidget* parent);
    void setup(Weather& weather);
private:
    bool eventFilter(QObject *object, QEvent *event);
    int calculateEndScrollBarValue(int delta);
    QVBoxLayout* scrollAreaLayout;
};

#endif // DAILYFORECASTSCROLLAREA_H

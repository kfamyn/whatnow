#ifndef SUNWIDGET_H
#define SUNWIDGET_H

#include "informationwidget.h"
#include <QObject>
#include <QWidget>
#include <QLabel>

const QString SUN_WIDGET_STYLESHEET = "color: qconicalgradient(cx:1, cy:0, angle:270, stop:0 rgba(255, 255, 255, 255), stop:1 rgba(0, 0, 0, 255))";

class SunWidget : public InformationWidget
{
    Q_OBJECT
public:
    SunWidget(QWidget *parent = nullptr);
public slots:
    void updateInfo(int dayIndex) final;
private:
    QString sunriseTime;
    QString sunsetTime;
    int sunPosition;
    QLabel* sunCurve;
    QLabel* sun;
    QLabel* sunriseTimeLabel;
    QLabel* sunsetTimeLabel;
};

#endif // SUNWIDGET_H

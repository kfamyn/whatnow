#ifndef SUNWIDGET_H
#define SUNWIDGET_H

#include "informationwidget.h"
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>

const QString SUN_WIDGET_STYLESHEET = "color: qconicalgradient(cx:1, cy:0, angle:270, stop:0 rgba(255, 255, 255, 255), stop:1 rgba(0, 0, 0, 255))";

class SunWidget : public InformationWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal sunPosition MEMBER m_sunPosition WRITE setSunPosition)
public:
    SunWidget(QWidget *parent = nullptr);
    QPoint cartesianToQPoint(int x, int y);
    QPoint qPointToCartesian(QPoint qPoint);
public slots:
    void updateInfo(int dayIndex) final;
    void setSunPosition(int currentTimeInSeconds);
private:
    QString sunriseTime;
    QString sunsetTime;
    qreal m_sunPosition;
    QLabel* sunCurve;
    QLabel* sun;
    QLabel* sunriseTimeLabel;
    QLabel* sunsetTimeLabel;

    QPropertyAnimation *widgetFadeAnimation(QGraphicsEffect *widgetGraphicsEffect, int duration, QEasingCurve easingCurve, QAbstractAnimation::Direction direction);
    void animateSunPosition();
};

#endif // SUNWIDGET_H

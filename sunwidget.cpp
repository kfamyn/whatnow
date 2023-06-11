#include "sunwidget.h"
#include "format.hpp"
#include <QPropertyAnimation>
#include <chrono>
#include <QDateTime>

SunWidget::SunWidget(QWidget *parent): InformationWidget(parent){
    m_sunPosition = 0;
    sunriseTime = "";
    sunsetTime = "";
    background = new QLabel(this);
    this->setBackground(":/background/assets/backgrounds/sunWidgetBackground.png", QSize(281, 132));
    this->setHeader("SUN");
    sun = createPixmapLabel(":/additionalWeatherIcons/assets/additionalWeatherIcons/sun.png", QSize(31, 31));
    sunCurve = createPixmapLabel(":/additionalWeatherIcons/assets/additionalWeatherIcons/sunCurve.png", QSize(295, 91));
    sunriseTimeLabel = createFixedSizeTextLabel("X:XX AM", 10, QFont::Normal, QSize(71, 16));
    sunsetTimeLabel = createFixedSizeTextLabel("X:XX PM", 10, QFont::Normal, QSize(71, 16));

    sunCurve->move(-8, 33);
    sunriseTimeLabel->move(4, 51);
    sunsetTimeLabel->move(207, 51);
    sun->move(168, 39);
    sun->raise();
}

void SunWidget::updateInfo(int dayIndex)
{
    if (dayIndex == 0){
        sunriseTime = QString::fromStdString(formatTime(weather->getCurrentConditions("sunrise"), HOURS_AND_MINUTES));
        sunsetTime = QString::fromStdString(formatTime(weather->getCurrentConditions("sunset"), HOURS_AND_MINUTES));
    }
    else {
        sunriseTime = QString::fromStdString(formatTime(weather->getValue(dayIndex, "sunrise"), HOURS_AND_MINUTES));
        sunsetTime = QString::fromStdString(formatTime(weather->getValue(dayIndex, "sunset"), HOURS_AND_MINUTES));
    }
    sunriseTimeLabel->setText(sunriseTime);
    sunsetTimeLabel->setText(sunsetTime);

    if (dayIndex == 0){
        int currentSecond = QDateTime::currentDateTime().time().hour()*24 + QDateTime::currentDateTime().time().minute() * 60 + QDateTime::currentDateTime().time().second() * 60;
        QPropertyAnimation* sunPositionAnimation = new QPropertyAnimation(this, "sunPosition");
        sunPositionAnimation->setDuration(500);
        sunPositionAnimation->setStartValue(0);
        sunPositionAnimation->setEndValue(currentSecond);
        sunPositionAnimation->setEasingCurve(QEasingCurve::OutCubic);
        sunPositionAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        m_sunPosition = currentSecond;
    }
}

QPoint SunWidget::cartesianToQPoint(int x, int y)
{
    return QPoint(x, this->parentWidget()->size().height() - y);
}

QPoint SunWidget::qPointToCartesian(QPoint qPoint)
{
    return QPoint(qPoint.x(), this->parentWidget()->size().height()-qPoint.y());
}

void SunWidget::setSunPosition(int currentTimeInSeconds){
    static const float mathematicalExpectation = 2.07;
    static const float standartDeviation = 0;
    static const float X_COORDINATE_RANGE = 4.52;
    static const float Y_COORDINATE_RANGE = 0.263;
    double x = (currentTimeInSeconds / (86400/(X_COORDINATE_RANGE*2))) - X_COORDINATE_RANGE;
    qDebug() << x;
    double y = (1/(mathematicalExpectation*sqrt(2*std::atan(1)*4)))*std::exp(-0.5*std::pow((x - standartDeviation) / mathematicalExpectation, 2));
    y += 0.034;
    x -= 0.49;
    double sunX = (background->size().width()/(X_COORDINATE_RANGE * 2)) * x + background->size().width() / 2;
    double sunY = (background->size().height()/Y_COORDINATE_RANGE) * y;
    //qDebug()<< sunX << ", " << sunY << "\n";
    sun->move(cartesianToQPoint(sunX, sunY));
}

#include "sunwidget.h"
#include "format.hpp"

SunWidget::SunWidget(QWidget *parent): InformationWidget(parent){
    sunPosition = 0;
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
}

QPoint SunWidget::cartesianToQPoint(int x, int y)
{
    return QPoint(x, this->parentWidget()->size().height() - y);
}

QPoint SunWidget::qPointToCartesian(QPoint qPoint)
{
    return QPoint(qPoint.x(), this->parentWidget()->size().height()-qPoint.y());
}

void SunWidget::updateSunPosition(int currentTimeInSeconds){
    static const float mathematicalExpectation = 2.07;
    static const float standartDeviation = 0;
    double x = (currentTimeInSeconds / (86400/(4.63*2))) - 4.63;
    qDebug() << x;
    double y = (1/(mathematicalExpectation*sqrt(2*std::atan(1)*4)))*std::exp(-0.5*std::pow((x - standartDeviation) / mathematicalExpectation, 2));
    y += 0.037;
    x -= 0.5;
    double sunX = (background->size().width()/(4.63 * 2)) * x + background->size().width() / 2;
    double sunY = (background->size().height()/0.265) * y;
    //qDebug()<< sunX << ", " << sunY << "\n";
    sun->move(cartesianToQPoint(sunX, sunY));
}

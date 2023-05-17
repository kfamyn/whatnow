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
    else{
        sunriseTime = QString::fromStdString(formatTime(weather->getValue(dayIndex, "sunrise"), HOURS_AND_MINUTES));
        sunsetTime = QString::fromStdString(formatTime(weather->getValue(dayIndex, "sunset"), HOURS_AND_MINUTES));
    }
    sunriseTimeLabel->setText(sunriseTime);
    sunsetTimeLabel->setText(sunsetTime);
}

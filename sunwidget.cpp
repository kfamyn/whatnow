#include "sunwidget.h"

SunWidget::SunWidget(QWidget *parent): InformationWidget(parent){
    sunPosition = 0;
    background = new QLabel(this);
    this->setBackground(":/background/assets/backgrounds/sunWidgetBackground.png", QSize(281, 132));
    this->setHeader("SUN");
    sun = createPixmapLabel(":/additionalWeatherIcons/assets/additionalWeatherIcons/sun.png", QSize(31, 31));
    sunCurve = createPixmapLabel(":/additionalWeatherIcons/assets/additionalWeatherIcons/sunCurve.png", QSize(295, 91));
    sunriseTime = createFixedSizeTextLabel("X:XX AM", 10, QFont::Normal, QSize(71, 16));
    sunsetTime = createFixedSizeTextLabel("X:XX PM", 10, QFont::Normal, QSize(71, 16));

    sunCurve->move(-8, 33);
    sunriseTime->move(4, 51);
    sunsetTime->move(207, 51);
    sun->move(168, 39);
}

void SunWidget::updateInfo(int dayIndex)
{

}

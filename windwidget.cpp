#include "windwidget.h"
#include <QFontDatabase>

WindWidget::WindWidget(QWidget *parent) : InformationWidget(parent){
    windSpeed = 0;
    windDirection = 0;
    background = new QLabel(this);
    this->setHeader("WIND");
    QFontDatabase::addApplicationFont(":/fonts/assets/Fonts/SFPro/SFProDisplay-Semibold.ttf");
    QFont SFPro = QFont("SF Pro Display", 12, 0);
    windSpeedLabel = createTextLabel("X M/S", SFPro, 10, QFont::Light, WIND_WIDGET_TEXT_STYLESHEET, QSize(60, 16));
    arrow = createPixmapLabel(":/additionalWeatherIcons/assets/additionalWeatherIcons/sun.png", QSize(31, 31));
    compass = createPixmapLabel(":/additionalWeatherIcons/assets/additionalWeatherIcons/compass.png", QSize(87, 87));
    south = createTextLabel("S", SFPro, 10, QFont::Light);
    east = createTextLabel("E", SFPro, 10, QFont::Light);
    north = createTextLabel("N", SFPro, 10, QFont::Light);
    west = createTextLabel("W", SFPro, 10, QFont::Light);

    windSpeedLabel->move(39, 68);
    arrow->move(79, 26);
    compass->move(24, 33);
    south->move(57, 23);
    east->move(100, 66);
    north->move(57, 109);
    west->move(15, 66);
}

void WindWidget::setup(Weather *weather)
{
    this->weather = weather;
    updateInfo(0);
}

void WindWidget::updateInfo(int dayIndex)
{

}

QLabel *WindWidget::createPixmapLabel(QString path, QSize size){
    QLabel* newLabel = new QLabel(this);
    newLabel->setFixedSize(size);
    newLabel->setPixmap(QPixmap(path));
    newLabel->setScaledContents(true);
    return newLabel;
}

QLabel *WindWidget::createTextLabel(QString text, QFont font, int fontSize, QFont::Weight weight, QString styleSheet, QSize labelSize)
{
    QLabel* textLabel = new QLabel(this);
    textLabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    textLabel->setText(text);
    font.setWeight(weight);
    font.setPointSize(fontSize);
    textLabel->setFont(font);
    textLabel->setStyleSheet(styleSheet);
    textLabel->setFixedSize(labelSize);
    return textLabel;
}
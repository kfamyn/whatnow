#include "hourlyforecastwidget.h"


HourlyForecastWidget::HourlyForecastWidget(QWidget *parent): QWidget(parent){}

void HourlyForecastWidget::setup(Weather &weather)
{
    background = new QLabel(this);
    this->setFixedSize(677, 360);
    scrollAreaWidgetContents = new QWidget(this);
    QHBoxLayout* scrollLayout = new QHBoxLayout(scrollAreaWidgetContents);
    scrollLayout->setSpacing(10);
    for (int index = 0; index < 24; ++index) {
        QString iconURL = ":/weatherIcons/assets/weatherIcons/";
        iconURL += QString::fromStdString(weather.getHourlyConditions(0, index, "icon"));
        iconURL += ".png";
        QString temperature = QString::fromStdString(weather.getHourlyConditions(0, index, "temp"));
        QString date = QString::fromStdString(weather.getValue(index, "datetime"));
        QString time = QString::fromStdString(weather.getHourlyConditions(0, index, "datetime"));
        QString precipitationProbability = QString::fromStdString(weather.getHourlyConditions(0, index, "precipprob"));
        HourlyForecastLine* hourlyForecastLine = new HourlyForecastLine(this);
        hourlyForecastLine->setup(date, time, iconURL, precipitationProbability, temperature);
        scrollLayout->addWidget(hourlyForecastLine);
    }
    scrollAreaWidgetContents->setStyleSheet("background-color:transparent;");
    widgetScrollarea = new SmoothScrollArea(this);
    widgetScrollarea->setup();
    widgetScrollarea->setupContents(scrollAreaWidgetContents, SmoothScrollArea::HORIZONTAL);
}

void HourlyForecastWidget::setBackground(QString path){

    background->setScaledContents(true);
    background->setFixedSize(677, 360);
    background->setPixmap(path);
    QImage img(path);
    QBitmap mask = QBitmap::fromImage(img.scaled(677, 360, Qt::IgnoreAspectRatio, Qt::SmoothTransformation).createAlphaMask());
    widgetScrollarea->setMask(mask);
}

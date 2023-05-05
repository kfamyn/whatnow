#include "dailyforecastwidget.h"
#include "format.hpp"

DailyForecastWidget::DailyForecastWidget(QWidget *parent) : WeatherWidget<DailyForecastLine>(parent){
    background = new QLabel(this);
    scrollAreaWidgetContents = new QWidget(this);
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollAreaWidgetContents);//
    for (int index = 0; index < 14; ++index) {
        forecastLines.append(new DailyForecastLine(this));
        scrollLayout->addWidget(forecastLines[index]);
        forecastLines[index]->getIndex() = index;
    }
    scrollAreaWidgetContents->setStyleSheet("background-color:transparent;");
    scrollAreaWidgetContents->setGeometry(0, 0, 340, 324); //default daily forecast geometry
    widgetScrollarea = new SmoothScrollArea(this);
    widgetScrollarea->setupContents(scrollAreaWidgetContents, SmoothScrollArea::VERTICAL);
    scrollAreaWidgetContents->setCursor(Qt::PointingHandCursor);
}

void DailyForecastWidget::setup(Weather &weather)
{
    this->weather = &weather;
    fillDailyForecast();
}

void DailyForecastWidget::fillDailyForecast()
{
    for (int index = 0; index < 14; ++index) {
        QString iconURL = createIconURL(index);
        QString temperatureDay = QString::number(std::stoi(weather->getValue(index, "tempmax")));
        QString temperatureNight = QString::number(std::stoi(weather->getValue(index, "tempmin")));
        QString date = QString::fromStdString(weather->getValue(index, "datetime"));
        int day = date.mid(8, 2).toInt();
        int month = date.mid(5, 2).toInt();
        int year = date.mid(0, 4).toInt();
        QString dayOfWeek = QString::fromStdString(formatDayOfWeek(day, month, year));
        forecastLines[index]->fill(iconURL, temperatureDay, temperatureNight, dayOfWeek);
    }
}

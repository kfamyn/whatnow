#include "hourlyforecastwidget.h"
#include "format.hpp"

void HourlyForecastWidget::setup(Weather &weather)
{
    this->weather = &weather;
    background = new QLabel(this);
    scrollAreaWidgetContents = new QWidget(this);
    QHBoxLayout* scrollLayout = new QHBoxLayout(scrollAreaWidgetContents);
    scrollLayout->setSpacing(20);
    scrollLayout->setContentsMargins(25, 0, 25, 0);
    for (int index = 0; index < 24; ++index) {
        forecastLines.append(new HourlyForecastLine(this));
        forecastLines[index]->setup("date", "time", "iconURL", "precipitationProbability", "temperature");
        scrollLayout->addWidget(forecastLines[index]);
    }
    fillCurrentHourlyForecast();
    scrollAreaWidgetContents->setStyleSheet("background-color:transparent;");
    scrollAreaWidgetContents->setGeometry(0, 0, 677, 360); //default hourly forecast geometry
    widgetScrollarea = new SmoothScrollArea(this);
    widgetScrollarea->setup();
    widgetScrollarea->setupContents(scrollAreaWidgetContents, SmoothScrollArea::HORIZONTAL);
}

void HourlyForecastWidget::updateHourlyForecast(int dayIndex)
{
    if (dayIndex == 0) {
        fillCurrentHourlyForecast();
    }
    else {
        for (int index = 0; index < 24; ++index) {
            QString iconURL = createIconURL(dayIndex, index);
            QString temperature = QString::fromStdString(formatTemperature(weather->getHourlyConditions(dayIndex, index, "temp")));
            QString date = QString::fromStdString(formatDate(weather->getValue(dayIndex, "datetime")));
            QString time = QString::fromStdString(formatTime(weather->getHourlyConditions(dayIndex, index, "datetime")));
            QString precipitationProbability = QString::number(std::stoi(weather->getHourlyConditions(dayIndex, index, "precipprob")));
            forecastLines[index]->fill(date, time , iconURL, precipitationProbability, temperature);
        }
    }
}

void HourlyForecastWidget::fillCurrentHourlyForecast()
{
    std::time_t timeT = std::time(NULL);
    std::string timeStdString = std::ctime(&timeT);
    int currentHour = std::stoi(timeStdString.substr(timeStdString.size() - 14, 2));
    for (int index = 0; index < 24; ++index) {
        int hourToGet = (currentHour + index) % 24;
        int dayToGet = (currentHour + index) / 24;
        QString iconURL = createIconURL(dayToGet, hourToGet);
        QString temperature = QString::fromStdString(formatTemperature(weather->getHourlyConditions(dayToGet, hourToGet, "temp")));
        QString date = QString::fromStdString(formatDate(weather->getValue(dayToGet, "datetime")));
        QString time = QString::fromStdString(formatTime(weather->getHourlyConditions(dayToGet, hourToGet, "datetime")));
        QString precipitationProbability = QString::number(std::stoi(weather->getHourlyConditions(dayToGet, hourToGet, "precipprob")));
        forecastLines[index]->fill(date, time, iconURL, precipitationProbability, temperature);
    }
}

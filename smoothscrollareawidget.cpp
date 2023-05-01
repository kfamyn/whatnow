#include "smoothscrollareawidget.h"
#include "format.hpp"

SmoothScrollAreaWidget::SmoothScrollAreaWidget(QWidget *parent): QWidget(parent){}

void SmoothScrollAreaWidget::setup(Weather &weather, contents typeOfContents)
{
    this->weather = &weather;
    switch (typeOfContents){
    case DAILYFORECAST:
        setupDailyForecast();
        break;
    case HOURLYFORECAST:
        setupHourlyForecast();
        break;
    case NEWS:
        break;
    }
}

void SmoothScrollAreaWidget::setBackground(QString path, QSize size){
    this->setFixedSize(size);
    background->setScaledContents(true);
    background->setFixedSize(size);
    background->setPixmap(path);
    QImage img(path);
    QBitmap mask = QBitmap::fromImage(img.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation).createAlphaMask());
    widgetScrollarea->setMask(mask);
}

HourlyForecastLine *SmoothScrollAreaWidget::getHourlyForecastLine(int index)
{
    return hourlyForecastLines[index];
}

DailyForecastLine *SmoothScrollAreaWidget::getDailyForecastLine(int index)
{
    return dailyForecastLines[index];
}

QWidget *SmoothScrollAreaWidget::getWidgetContents()
{
    return scrollAreaWidgetContents;
}

void SmoothScrollAreaWidget::updateHourlyForecast(int dayIndex)
{
    if (dayIndex == 0) {
        fillCurrentHourlyForecast();
    }
    else {
        for (int index = 0; index < 24; ++index) {
            QString iconURL = ":/weatherIcons/assets/weatherIcons/";
            iconURL += QString::fromStdString(weather->getHourlyConditions(dayIndex, index, "icon"));
            iconURL += ".png";
            QString temperature = QString::fromStdString(formatTemperature(weather->getHourlyConditions(dayIndex, index, "temp")));
            QString date = QString::fromStdString(formatDate(weather->getValue(dayIndex, "datetime")));
            QString time = QString::fromStdString(formatTime(weather->getHourlyConditions(dayIndex, index, "datetime")));
            QString precipitationProbability = QString::number(std::stoi(weather->getHourlyConditions(dayIndex, index, "precipprob")));
            hourlyForecastLines[index]->fill(date, time , iconURL, precipitationProbability, temperature);
        }
    }
}

void SmoothScrollAreaWidget::setupDailyForecast()
{
    background = new QLabel(this);
    scrollAreaWidgetContents = new QWidget(this);
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollAreaWidgetContents);
    for (int index = 0; index < 14; ++index) {
        dailyForecastLines[index] = new DailyForecastLine(this);
        dailyForecastLines[index]->setup("iconURL", "temperatureDay", "temperatureNight", "dayOfWeek", index);
        scrollLayout->addWidget(dailyForecastLines[index]);
    }
    fillDailyForecast();
    scrollAreaWidgetContents->setStyleSheet("background-color:transparent;");
    scrollAreaWidgetContents->setGeometry(0, 0, 340, 324); //default daily forecast geometry
    widgetScrollarea = new SmoothScrollArea(this);
    widgetScrollarea->setup();
    widgetScrollarea->setupContents(scrollAreaWidgetContents, SmoothScrollArea::VERTICAL);
    scrollAreaWidgetContents->setCursor(Qt::PointingHandCursor);
}

void SmoothScrollAreaWidget::setupHourlyForecast()
{
    background = new QLabel(this);
    scrollAreaWidgetContents = new QWidget(this);
    QHBoxLayout* scrollLayout = new QHBoxLayout(scrollAreaWidgetContents);
    scrollLayout->setSpacing(20);
    scrollLayout->setContentsMargins(25, 0, 25, 0);
    for (int index = 0; index < 24; ++index) {
        hourlyForecastLines[index] = new HourlyForecastLine(this);
        hourlyForecastLines[index]->setup("date", "time", "iconURL", "precipitationProbability", "temperature");
        scrollLayout->addWidget(hourlyForecastLines[index]);
    }
    fillCurrentHourlyForecast();
    scrollAreaWidgetContents->setStyleSheet("background-color:transparent;");
    scrollAreaWidgetContents->setGeometry(0, 0, 677, 360); //default hourly forecast geometry
    widgetScrollarea = new SmoothScrollArea(this);
    widgetScrollarea->setup();
    widgetScrollarea->setupContents(scrollAreaWidgetContents, SmoothScrollArea::HORIZONTAL);
}

void SmoothScrollAreaWidget::fillCurrentHourlyForecast()
{
    std::time_t timeT = std::time(NULL);
    std::string timeStdString = std::ctime(&timeT);
    int currentHour = std::stoi(timeStdString.substr(timeStdString.size() - 14, 2));
    for (int index = 0; index < 24; ++index) {
        int hourToGet = (currentHour + index) % 24;
        int dayToGet = (currentHour + index) / 24;
        QString iconURL = ":/weatherIcons/assets/weatherIcons/";
        iconURL += QString::fromStdString(weather->getHourlyConditions(dayToGet, hourToGet, "icon"));
        iconURL += ".png";
        QString temperature = QString::fromStdString(formatTemperature(weather->getHourlyConditions(dayToGet, hourToGet, "temp")));
        QString date = QString::fromStdString(formatDate(weather->getValue(dayToGet, "datetime")));
        QString time = QString::fromStdString(formatTime(weather->getHourlyConditions(dayToGet, hourToGet, "datetime")));
        QString precipitationProbability = QString::number(std::stoi(weather->getHourlyConditions(dayToGet, hourToGet, "precipprob")));
        hourlyForecastLines[index]->fill(date, time, iconURL, precipitationProbability, temperature);
    }
}

void SmoothScrollAreaWidget::fillDailyForecast()
{
    for (int index = 0; index < 14; ++index) {
        QString iconURL = ":/weatherIcons/assets/weatherIcons/";
        iconURL += QString::fromStdString(weather->getValue(index, "icon"));
        iconURL += ".png";
        QString temperatureDay = QString::number(std::stoi(weather->getValue(index, "tempmax")));
        QString temperatureNight = QString::number(std::stoi(weather->getValue(index, "tempmin")));
        QString date = QString::fromStdString(weather->getValue(index, "datetime"));
        int day = date.mid(8, 2).toInt();
        int month = date.mid(5, 2).toInt();
        int year = date.mid(0, 4).toInt();
        QString dayOfWeek = QString::fromStdString(formatDayOfWeek(day, month, year));
        dailyForecastLines[index]->fill(iconURL, temperatureDay, temperatureNight, dayOfWeek);
    }
}

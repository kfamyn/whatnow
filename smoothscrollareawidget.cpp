#include "smoothscrollareawidget.h"
#include "hourlyforecastline.h"
#include "dailyforecastline.h"
#include "format.hpp"

SmoothScrollAreaWidget::SmoothScrollAreaWidget(QWidget *parent): QWidget(parent){}

void SmoothScrollAreaWidget::setup(Weather &weather, contents typeOfContents)
{
    switch (typeOfContents){
    case DAILYFORECAST:
        setupDailyForecast(weather);
        break;
    case HOURLYFORECAST:
        setupHourlyForecast(weather);
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

void SmoothScrollAreaWidget::setupDailyForecast(Weather &weather)
{
    background = new QLabel(this);
    scrollAreaWidgetContents = new QWidget(this);
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollAreaWidgetContents);
    for (int index = 0; index < 14; ++index) {
        QString iconURL = ":/weatherIcons/assets/weatherIcons/";
        iconURL += QString::fromStdString(weather.getValue(index, "icon"));
        iconURL += ".png";
        QString temperatureDay = QString::number(std::stoi(weather.getValue(index, "tempmax")));
        QString temperatureNight = QString::number(std::stoi(weather.getValue(index, "tempmin")));
        QString date = QString::fromStdString(weather.getValue(index, "datetime"));
        int year = date.mid(0, 4).toInt();
        int month = date.mid(5, 2).toInt();
        int day = date.mid(8, 2).toInt();
        QString dayOfWeek = QString::fromStdString(formatDayOfWeek(year, month, day));
        DailyForecastLine* forecastLine = new DailyForecastLine(this);
        forecastLine->setup(iconURL, temperatureDay, temperatureNight, dayOfWeek);
        scrollLayout->addWidget(forecastLine);
    }
    scrollAreaWidgetContents->setStyleSheet("background-color:transparent;");
    scrollAreaWidgetContents->setGeometry(0, 0, 340, 324); //default daily forecast geometry
    widgetScrollarea = new SmoothScrollArea(this);
    widgetScrollarea->setup();
    widgetScrollarea->setupContents(scrollAreaWidgetContents, SmoothScrollArea::VERTICAL);
}

void SmoothScrollAreaWidget::setupHourlyForecast(Weather &weather)
{
    background = new QLabel(this);
    scrollAreaWidgetContents = new QWidget(this);
    QHBoxLayout* scrollLayout = new QHBoxLayout(scrollAreaWidgetContents);
    scrollLayout->setSpacing(20);
    scrollLayout->setContentsMargins(25, 0, 25, 0);
    std::time_t timeT = std::time(NULL);
    std::string timeStdString = std::ctime(&timeT);
    int currentHour = std::stoi(timeStdString.substr(timeStdString.size() - 14, 2));
    for (int index = 0; index < 24; ++index) {
        int hourToGet = (currentHour + index) % 24;
        int dayToGet = (currentHour + index) / 24;
        QString iconURL = ":/weatherIcons/assets/weatherIcons/";
        iconURL += QString::fromStdString(weather.getHourlyConditions(dayToGet, hourToGet, "icon"));
        iconURL += ".png";
        QString temperature = QString::fromStdString(formatTemperature(weather.getHourlyConditions(dayToGet, hourToGet, "temp")));
        QString date = QString::fromStdString(formatDate(weather.getValue(dayToGet, "datetime")));
        QString time = QString::fromStdString(formatTime(weather.getHourlyConditions(dayToGet, hourToGet, "datetime")));
        QString precipitationProbability = QString::number(std::stoi(weather.getHourlyConditions(dayToGet, hourToGet, "precipprob")));
        HourlyForecastLine* hourlyForecastLine = new HourlyForecastLine(this);
        hourlyForecastLine->setup(date, time, iconURL, precipitationProbability, temperature);
        scrollLayout->addWidget(hourlyForecastLine);
    }
    scrollAreaWidgetContents->setStyleSheet("background-color:transparent;");
    scrollAreaWidgetContents->setGeometry(0, 0, 677, 360); //default hourly forecast geometry
    widgetScrollarea = new SmoothScrollArea(this);
    widgetScrollarea->setup();
    widgetScrollarea->setupContents(scrollAreaWidgetContents, SmoothScrollArea::HORIZONTAL);
}

#include "hourlyforecastwidget.h"


HourlyForecastWidget::HourlyForecastWidget(QWidget *parent): QWidget(parent){}

void HourlyForecastWidget::setup(Weather &weather)
{
    std::time_t timeT = std::time(NULL);
    std::string timeStdString = std::ctime(&timeT);
    int currentHour = std::stoi(timeStdString.substr(timeStdString.size() - 14, 2));
    background = new QLabel(this);
    scrollAreaWidgetContents = new QWidget(this);
    QHBoxLayout* scrollLayout = new QHBoxLayout(scrollAreaWidgetContents);
    scrollLayout->setSpacing(10);
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
    widgetScrollarea = new SmoothScrollArea(this);
    widgetScrollarea->setup();
    widgetScrollarea->setupContents(scrollAreaWidgetContents, SmoothScrollArea::HORIZONTAL);
}

void HourlyForecastWidget::setBackground(QString path, QSize size){
    this->setFixedSize(size);
    background->setScaledContents(true);
    background->setFixedSize(size);
    background->setPixmap(path);
    QImage img(path);
    QBitmap mask = QBitmap::fromImage(img.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation).createAlphaMask());
    widgetScrollarea->setMask(mask);
}

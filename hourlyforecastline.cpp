#include "hourlyforecastline.h"

HourlyForecastLine::HourlyForecastLine(QWidget *parent): QWidget(parent){}

void HourlyForecastLine::setup(QString date, QString time, QString iconURL, QString precipitationProbability, QString temperature)
{
    this->setFixedSize(141, 351);
    this->setStyleSheet("background-color:transparent;");
    dateLabel = createTextLabel(date, 13, QFont::Light, "color: qconicalgradient(cx:1, cy:0, angle:270, stop:0 rgba(255, 255, 255, 255), stop:1 rgba(0, 0, 0, 255))", Qt::AlignHCenter | Qt::AlignBottom);
    timeLabel = createTextLabel(time, 24, QFont::Normal, "color: qconicalgradient(cx:1, cy:0, angle:70, stop:0.76089 rgba(255, 255, 255, 255), stop:0.611285 rgba(50, 50, 50, 255))", Qt::AlignHCenter | Qt::AlignVCenter);
    iconVerticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Fixed, QSizePolicy::Fixed);
    weatherIconLabel = createIconLabel(iconURL, 120);
    setupPrecipitationProbabilityLayout(precipitationProbability);
    setupTemperatureLayout(temperature);
    setupHourlyForecastLayout();
}

void HourlyForecastLine::updateForecast(QString date, QString time, QString iconURL, QString precipitationProbability, QString temperature)
{
    this->dateLabel->setText(date);
    this->timeLabel->setText(time);
    this->weatherIconLabel->setPixmap(QPixmap(iconURL));
    this->precipitationProbabilityLabel->setText(precipitationProbability.append("%"));
    this->temperatureLabel->setText(temperature);
}

QLabel* HourlyForecastLine::createTextLabel(QString text, int fontSize, QFont::Weight weight, QString styleSheet, Qt::Alignment alignment, QSizePolicy::Policy policy1, QSizePolicy::Policy policy2)
{
    QFontDatabase::addApplicationFont(":/fonts/assets/Fonts/SFPro/SFProDisplay-Regular.ttf");
    QFont SFPro = QFont("SF Pro Display", fontSize, 0);
    QLabel* textLabel = new QLabel(this);
    textLabel->setText(text);
    SFPro.setWeight(weight);
    textLabel->setFont(SFPro);
    textLabel->setSizePolicy(policy1, policy2);
    textLabel->setStyleSheet(styleSheet);
    textLabel->setAlignment(alignment);
    return textLabel;
}

QLabel *HourlyForecastLine::createIconLabel(QString iconURL, int size)
{
    QLabel* iconLabel = new QLabel(this);
    iconLabel->setFixedSize(size, size);
    iconLabel->setScaledContents(true);
    iconLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    iconLabel->setPixmap(QPixmap(iconURL));
    return iconLabel;
}

void HourlyForecastLine::setupPrecipitationProbabilityLayout(QString& precipitationProbability)
{
    precipitationProbabilityLeftSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
    QString precipitationProbabilityProcessed = precipitationProbability == "0" ? "" : precipitationProbability.append("%");
    precipitationProbabilityLabel = createTextLabel(precipitationProbabilityProcessed, 13, QFont::Light, "color: qconicalgradient(cx:1, cy:0, angle:78, stop:0.72089 rgba(255, 255, 255, 255), stop:0.131285 rgba(0, 0, 0, 255))", Qt::AlignRight | Qt::AlignBottom);
    precipitationIconLabel = new QLabel(this);
    QString precipitationIconPath = precipitationProbability == "0" ? ":/additionalWeatherIcons/assets/additionalWeatherIcons/NoPrecipitations.png" : ":/additionalWeatherIcons/assets/additionalWeatherIcons/Precipitations.png";
    precipitationIconLabel = createIconLabel(precipitationIconPath, 15);
    precipitationIconLayout = new QVBoxLayout();
    precipitationIconLayout->addWidget(precipitationIconLabel);
    precipitationIconLayout->setContentsMargins(0, 9, 0, 2);
    precipitationProbabilityRightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);

    precipitationProbabilityLayout = new QHBoxLayout();
    precipitationProbabilityLayout->setSpacing(2);
    precipitationProbabilityLayout->addSpacerItem(precipitationProbabilityLeftSpacer);
    precipitationProbabilityLayout->addWidget(precipitationProbabilityLabel);
    precipitationProbabilityLayout->addLayout(precipitationIconLayout);
    precipitationProbabilityLayout->addSpacerItem(precipitationProbabilityRightSpacer);
}

void HourlyForecastLine::setupTemperatureLayout(QString& temperature)
{
    temperatureLeftSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
    temperatureLabel = createTextLabel(temperature, 39, QFont::Normal, "color: qconicalgradient(cx:0.5, cy:0.5, angle:0, stop:0 rgba(255,255,255,0), stop:0.9 rgba(255,255,255,255),  stop:1 rgba(202, 162, 203, 255));", Qt::AlignTop | Qt::AlignRight);
    celciusLabel = createTextLabel("°C", 24, QFont::Normal, "color: qconicalgradient(cx:0.5, cy:0.5, angle:0, stop:0 rgba(255,255,255,0), stop:0.6 rgba(255,255,255,255),  stop:1 rgba(202, 162, 203, 255));", Qt::AlignLeft | Qt::AlignTop);
    celciusLayout = new QVBoxLayout();
    celciusLayout->addWidget(celciusLabel);
    celciusLayout->setContentsMargins(0, 5, 0, 0);
    temperatureRightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);

    temperatureLayout = new QHBoxLayout();
    temperatureLayout->addSpacerItem(temperatureLeftSpacer);
    temperatureLayout->addWidget(temperatureLabel);
    temperatureLayout->addLayout(celciusLayout);
    temperatureLayout->addSpacerItem(temperatureRightSpacer);
}

void HourlyForecastLine::setupHourlyForecastLayout()
{
    hourlyForecastLayout = new QVBoxLayout(this);
    hourlyForecastLayout->setContentsMargins(9, 26, 9, 24);
    hourlyForecastLayout->setSpacing(6);
    hourlyForecastLayout->addWidget(dateLabel);
    hourlyForecastLayout->addWidget(timeLabel);
    hourlyForecastLayout->addSpacerItem(iconVerticalSpacer);
    hourlyForecastLayout->addWidget(weatherIconLabel);
    hourlyForecastLayout->addLayout(precipitationProbabilityLayout);
    hourlyForecastLayout->addLayout(temperatureLayout);
}



#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFontDatabase>
#include <QPropertyAnimation>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <QAbstractItemView>
#include <QGraphicsOpacityEffect>
#include <QPainter>
#include <QScrollArea>
#include <QScrollBar>
#include <QCommonStyle>
#include <QPainterPath>
#include <ctime>
#include <QSequentialAnimationGroup>
#include "format.hpp"
#include "dailyforecastwidget.h"
#include "smoothscrollareawidget.h"

void fadeWidget(QWidget* widget, int mode, int duration);

void setConditionsImage(QLabel* label, QString conditions);

QLabel* findForecastLabel(MainWindow* mainWindow, int index, QString labelName);

void setForecastImage(QLabel* label, int index, Weather& Weather);

void setForecast(MainWindow* mainWindow, QString labelName, void (&functionToSet)(QLabel* label, int index, Weather& Weather), Weather& Weather);

void setForecastConditions(MainWindow* mainWindow, Weather& Weather);

void setForecastTemperatureDay(MainWindow* mainWindow, Weather& Weather);

void setForecastTemperatureDay(QLabel* label, int index, Weather& Weather);

void setForecastTemperatureNight(QLabel* label, int index, Weather& Weather);

void setForecastDayOfWeek(QLabel* label, int index, Weather& Weather);

void setHourlyForecast(MainWindow* mainWindow, QString labelName, int offset, void (&functionToSet)(QLabel* label, int offset, int hour, Weather& Weather), Weather& Weather);

QLabel* findHourlyForecastLabel(MainWindow* mainWindow, int hour, QString labelName);

void setHourlyForecastImage(QLabel* label, int offset, int hour, Weather& Weather);

void setHourlyForecastDate(QLabel* label, int offset, int hour, Weather& Weather);

void setHourlyForecastTime(QLabel* label, int offset, int hour, Weather& Weather);

void setHourlyForecastPrecipitationProbability(QLabel* label, int offset, int hour, Weather& Weather);

void setHourlyForecastTemperature(QLabel* label, int offset, int hour, Weather& Weather);

void setHourlyForecastScrollBar(QScrollBar* scrollBar);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this-> setAttribute (Qt :: WA_TranslucentBackground);
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(100);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("qwidget{border-top-left-radius:15px;border-top-right-radius:5px;}");
    QFontDatabase::addApplicationFont(":/fonts/assets/Fonts/SFPro/SFProDisplay-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/assets/Fonts/SFPro/SFProDisplay-Black.ttf");
    QFontDatabase::addApplicationFont(":/fonts/assets/Fonts/SFPro/SFProDisplay-Semibold.ttf");
    QFont SFProSemibold17 = QFont("SF Pro Display", 17, 0);
    SFProSemibold17.setWeight(QFont::DemiBold);
    ui->CurrentLocation->setFont(SFProSemibold17);
    QFont forecastFont = ui->forecast1TemperatureDayDegrees->font();
    forecastFont.setWeight(QFont::DemiBold);
    ui->forecast1TemperatureDayDegrees->setFont(forecastFont);
    forecastFont = ui->forecast1TemperatureNightDegrees->font();
    forecastFont.setWeight(QFont::DemiBold);
    ui->forecast1TemperatureNightDegrees->setFont(forecastFont);

    Weather Weather("saint petersburg");
    ui->CurrentTemperature->setText(QString::number(std::stoi(Weather.getCurrentConditions("temp"))));
    ui->CurrentLocation->setText(QString::fromStdString(Weather.getAddress()));

    QFont currentTemperatureFont = ui->CurrentTemperature->font();
    switch (static_cast<int>((ui->CurrentTemperature->text()).toStdString().length())){
    case 1:
        ui->CurrentTemperatureLayout->setStretch(0, 1);
        ui->CurrentTemperatureLayout->setStretch(1, 1);
        currentTemperatureFont.setPointSize(108);
        ui->CurrentTemperature->setFont(currentTemperatureFont);
        break;
    case 2:
        ui->CurrentTemperatureLayout->setStretch(0, 6);
        ui->CurrentTemperatureLayout->setStretch(1, 4);
        currentTemperatureFont.setPointSize(108);
        ui->CurrentTemperature->setFont(currentTemperatureFont);
        break;
    case 3:
        ui->CurrentTemperatureLayout->setStretch(0, 2);
        ui->CurrentTemperatureLayout->setStretch(1, 1);
        currentTemperatureFont.setPointSize(96);
        ui->CurrentTemperature->setFont(currentTemperatureFont);
        break;
    default:
        break;
    }
    fadeWidget(ui->CurrentTemperature, 0, 450);
    fadeWidget(ui->DegreesCelcius, 0, 450);
    fadeWidget(ui->CurrentConditions, 0, 450);
    fadeWidget(ui->CurrentLocation, 0, 450);
    fadeWidget(ui->forecastScrollArea, 0, 450);
    fadeWidget(ui->hourlyForecastScrollArea, 0, 450);
    fadeWidget(ui->Exit, 0, 250);

    ui->forecastScrollArea->verticalScrollBar()->setStyle( new QCommonStyle );
    ui->hourlyForecastScrollArea->horizontalScrollBar()->setStyle( new QCommonStyle );
    setConditionsImage(ui->CurrentConditions, QString::fromStdString(Weather.getCurrentConditions("icon")));
    setForecast(this, "Conditions", setForecastImage, Weather);
    setForecast(this, "TemperatureDayDegrees", setForecastTemperatureDay, Weather);
    setForecast(this, "TemperatureNightDegrees", setForecastTemperatureNight, Weather);
    setForecast(this, "DayOfWeek", setForecastDayOfWeek, Weather);
    setHourlyForecast(this, "Icon", 0, setHourlyForecastImage, Weather);
    setHourlyForecast(this, "Date", 0, setHourlyForecastDate, Weather);
    setHourlyForecast(this, "Time", 0, setHourlyForecastTime, Weather);
    setHourlyForecast(this, "PrecipitationProbability", 0, setHourlyForecastPrecipitationProbability, Weather);
    setHourlyForecast(this, "TemperatureDegrees", 0, setHourlyForecastTemperature, Weather);
    setHourlyForecastScrollBar(ui->hourlyForecastScrollArea->horizontalScrollBar());

    ui->forecastScrollArea->setVisible(false);
    SmoothScrollAreaWidget* forecastWidget = new SmoothScrollAreaWidget(ui->widget);
    forecastWidget->setup(Weather, SmoothScrollAreaWidget::DAILYFORECAST);
    forecastWidget->setBackground(":/background/assets/backgrounds/Bottom_Left_Corner_Background.png", QSize(340, 324));
    fadeWidget(forecastWidget, 0, 450);

    SmoothScrollAreaWidget* hourlyForecastWidget = new SmoothScrollAreaWidget(ui->widget_7);
    hourlyForecastWidget->setup(Weather, SmoothScrollAreaWidget::HOURLYFORECAST);
    hourlyForecastWidget->setBackground(":/background/assets/backgrounds/Upper_Right_Corner_Background.png", QSize(677, 360));
    fadeWidget(hourlyForecastWidget, 0, 450);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Exit_clicked()
{
    qApp->exit();
}

void fadeWidget(QWidget* widget, int mode, int duration){ //0 - in, 1 - out
    QGraphicsOpacityEffect *widgetOpacity = new QGraphicsOpacityEffect(widget);
    widget->setGraphicsEffect(widgetOpacity);
    QPropertyAnimation *widgetOpacityAnimation = new QPropertyAnimation(widgetOpacity, "opacity");
    widgetOpacityAnimation->setDuration(duration);
    widgetOpacityAnimation->setStartValue(mode);
    widgetOpacityAnimation->setEndValue(1 - mode);
    widgetOpacityAnimation->setEasingCurve(QEasingCurve::InBack);
    widgetOpacityAnimation->start(QPropertyAnimation::DeleteWhenStopped);
}

void setForecast(MainWindow* mainWindow, QString labelName, void (&functionToSet)(QLabel* label, int index, Weather& Weather), Weather& Weather){ // makes a cycle of functionToSet functions for labels named forecast"Index""LabelName"
    for (int index = 1; index != 15; ++index){
        QLabel* forecastIndexLabel = findForecastLabel(mainWindow, index, labelName);
        functionToSet(forecastIndexLabel, index, Weather);
    }
}

QLabel* findForecastLabel(MainWindow* mainWindow, int index, QString labelName){
    QString forecastIndexLabelName = "forecast";
    forecastIndexLabelName.append(QString::number(index));
    forecastIndexLabelName.append(labelName);
    QLabel* forecastIndexLabel = mainWindow->findChild<QLabel*>(forecastIndexLabelName);
    return forecastIndexLabel;
}

void setForecastImage(QLabel* label, int index, Weather& Weather){
    QString path = ":/weatherIcons/assets/weatherIcons/";
    path += QString::fromStdString(Weather.getValue(index - 1, "icon"));
    path += ".png";
    QPixmap image(path);
    label->setPixmap(image);
    label->setFixedWidth(49);
    label->setFixedHeight(49);
    label->setScaledContents(true);
}

void setForecastTemperatureDay(QLabel* label, int index, Weather& Weather){
    label->setText(QString::number(std::stoi(Weather.getValue(index - 1, "tempmax"))));
    QFont forecastFont = label->font();
    forecastFont.setWeight(QFont::DemiBold);
    label->setFont(forecastFont);
}

void setForecastTemperatureNight(QLabel* label, int index, Weather& Weather){
    label->setText(QString::number(std::stoi(Weather.getValue(index - 1, "tempmin"))));
    QFont forecastFont = label->font();
    forecastFont.setWeight(QFont::DemiBold);
    label->setFont(forecastFont);
}

void setForecastDayOfWeek(QLabel* label, int index, Weather& Weather){
    QString date = QString::fromStdString(Weather.getValue(index - 1, "datetime"));

    int year = date.mid(0, 4).toInt();
    int month = date.mid(5,2).toInt();
    int day = date.mid(8,2).toInt();
    label->setText(QString::fromStdString(formatDayOfWeek(year, month, day)));
    //label->setText(QString::fromStdString(Weather.getValue(index - 1, "datetime")));
}

void setConditionsImage(QLabel* label, QString conditions){
    QString path = ":/weatherIcons/assets/weatherIcons/";
    path += conditions;
    path += ".png";
    QPixmap image(path);
    label->setPixmap(image);
    label->setScaledContents(true);
}

void setHourlyForecast(MainWindow* mainWindow, QString labelName, int offset, void (&functionToSet)(QLabel* label, int offset, int hour, Weather& Weather), Weather& Weather){ // makes a cycle of functionToSet functions for labels named hourlyForecast"LabelName"_"Index"
    for (int hour = 0; hour != 24; ++hour){
        QLabel* hourlyForecastIndexLabel = findHourlyForecastLabel(mainWindow, hour, labelName);
        functionToSet(hourlyForecastIndexLabel, offset, hour, Weather);
    }
}

QLabel* findHourlyForecastLabel(MainWindow* mainWindow, int hour, QString labelName){
    QString HourlyForecastIndexLabelName = "hourlyForecast";
    HourlyForecastIndexLabelName.append(labelName);
    HourlyForecastIndexLabelName.append("_");
    HourlyForecastIndexLabelName.append(QString::number(hour));
    QLabel* HourlyForecastLabel_index = mainWindow->findChild<QLabel*>(HourlyForecastIndexLabelName);
    return HourlyForecastLabel_index;
}

void setHourlyForecastImage(QLabel* label, int offset, int hour, Weather& Weather){
    QString path = ":/weatherIcons/assets/weatherIcons/";
    path += QString::fromStdString(Weather.getHourlyConditions(offset, hour, "icon"));
    path += ".png";
    QPixmap image(path);
    label->setPixmap(image);
    label->setScaledContents(true);
}

void setHourlyForecastDate(QLabel* label, int offset, int hour, Weather& Weather){
    label->setText(QString::fromStdString(formatDate(Weather.getValue(offset, "datetime"))));
}

void setHourlyForecastTime(QLabel* label, int offset, int hour, Weather& Weather){
    label->setText(QString::fromStdString(formatTime(Weather.getHourlyConditions(offset, hour, "datetime"))));
}

void setHourlyForecastPrecipitationProbability(QLabel* label, int offset, int hour, Weather& Weather){
    label->setText(QString::fromStdString(formatPrecipitationProbability(Weather.getHourlyConditions(offset, hour, "precipprob"))));
}

void setHourlyForecastTemperature(QLabel* label, int offset, int hour, Weather& Weather){
    label->setText(QString::fromStdString(formatTemperature(Weather.getHourlyConditions(offset, hour, "temp"))));
}

void setHourlyForecastScrollBar(QScrollBar* scrollBar){
    time_t now = time(0);
    std::string time = ctime(&now);
    if (time.length() == 25){
        scrollBar->setValue(167*std::stoi(time.substr(11, 2)));
    }
    else
        scrollBar->setValue(167*std::stoi(time.substr(10, 2)));
    qDebug()<<time.length();
}

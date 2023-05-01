#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "smoothscrollareawidget.h"

#include <QSequentialAnimationGroup>
#include <QSignalMapper>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setupAttributes();
    this->setupFonts();
    this->animateFadingIn();
    weather = new Weather("Los-Angeles");
    this->setupCurrentConditionsWidget();
    this->adjustCurrentTemperatureFont();

    ui->forecastScrollAreaSample->setVisible(false);
    dailyForecastWidget = new SmoothScrollAreaWidget(ui->DailyForecastWidget);
    dailyForecastWidget->setup(*weather, SmoothScrollAreaWidget::DAILYFORECAST);
    dailyForecastWidget->setBackground(":/background/assets/backgrounds/Bottom_Left_Corner_Background.png", QSize(340, 324));

    hourlyForecastWidget = new SmoothScrollAreaWidget(ui->HourlyForecastWidget);
    hourlyForecastWidget->setup(*weather, SmoothScrollAreaWidget::HOURLYFORECAST);
    hourlyForecastWidget->setBackground(":/background/assets/backgrounds/Upper_Right_Corner_Background.png", QSize(677, 360));
    this->fadeWidgetsIn();
    for (int index = 0; index < 14; ++index) {
        QObject::connect(dailyForecastWidget->getDailyForecastLine(index), SIGNAL(linePressed(int)), this, SLOT(dailyForecastLinePressed(int)));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Exit_clicked()
{
    qApp->exit();
}

void MainWindow::dailyForecastLinePressed(int dayIndex)
{
    QSignalMapper* signalMapper = new QSignalMapper(this) ;
    QGraphicsOpacityEffect *hourlyForecastWidgetOpacity = new QGraphicsOpacityEffect(hourlyForecastWidget);
    hourlyForecastWidget->setGraphicsEffect(hourlyForecastWidgetOpacity);

    QPropertyAnimation *hourlyForecastWidgetOpacityAnimation1 = new QPropertyAnimation(hourlyForecastWidgetOpacity, "opacity");
    hourlyForecastWidgetOpacityAnimation1->setDuration(200);
    hourlyForecastWidgetOpacityAnimation1->setStartValue(1);
    hourlyForecastWidgetOpacityAnimation1->setEndValue(0);
    hourlyForecastWidgetOpacityAnimation1->setEasingCurve(QEasingCurve::OutBack);

    QPropertyAnimation *hourlyForecastWidgetOpacityAnimation2 = new QPropertyAnimation(hourlyForecastWidgetOpacity, "opacity");
    hourlyForecastWidgetOpacityAnimation2->setDuration(200);
    hourlyForecastWidgetOpacityAnimation2->setStartValue(0);
    hourlyForecastWidgetOpacityAnimation2->setEndValue(1);
    hourlyForecastWidgetOpacityAnimation2->setEasingCurve(QEasingCurve::InBack);

    QSequentialAnimationGroup* animationSequence = new QSequentialAnimationGroup(this);
    animationSequence->addAnimation(hourlyForecastWidgetOpacityAnimation1);
    animationSequence->addAnimation(hourlyForecastWidgetOpacityAnimation2);
    animationSequence->start();

    connect(hourlyForecastWidgetOpacityAnimation1, SIGNAL(finished()), signalMapper, SLOT(map()));
    signalMapper->setMapping(hourlyForecastWidgetOpacityAnimation1, dayIndex);
    connect(signalMapper, SIGNAL(mappedInt(int)), hourlyForecastWidget, SLOT(updateHourlyForecast(int)));

}

void MainWindow::setupAttributes()
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("qwidget{border-top-left-radius:15px;border-top-right-radius:5px;}");
}

void MainWindow::setupFonts()
{
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
}

void MainWindow::animateFadingIn()
{
    QPropertyAnimation *mainWindowFadingIn = new QPropertyAnimation(this, "windowOpacity");
    mainWindowFadingIn->setDuration(100);
    mainWindowFadingIn->setStartValue(0);
    mainWindowFadingIn->setEndValue(1);
    mainWindowFadingIn->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::setupCurrentConditionsWidget()
{
    ui->CurrentTemperature->setText(QString::number(std::stoi(weather->getCurrentConditions("temp"))));
    ui->CurrentLocation->setText(QString::fromStdString(weather->getAddress()));
    QString path = ":/weatherIcons/assets/weatherIcons/";
    path += QString::fromStdString(weather->getCurrentConditions("icon"));
    path += ".png";
    ui->CurrentConditions->setPixmap(QPixmap(path));
    ui->CurrentConditions->setScaledContents(true);
}

void MainWindow::adjustCurrentTemperatureFont()
{
    QFont currentTemperatureFont = ui->CurrentTemperature->font();
    switch ((ui->CurrentTemperature->text()).toStdString().length()){
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
}

void MainWindow::fadeWidgetsIn()
{
    fadeWidget(ui->Exit, 0, 250)->start(QPropertyAnimation::DeleteWhenStopped);
    fadeWidget(ui->CurrentTemperature, 0, 450)->start(QPropertyAnimation::DeleteWhenStopped);
    fadeWidget(ui->DegreesCelcius, 0, 450)->start(QPropertyAnimation::DeleteWhenStopped);
    fadeWidget(ui->CurrentConditions, 0, 450)->start(QPropertyAnimation::DeleteWhenStopped);
    fadeWidget(ui->CurrentLocation, 0, 450)->start(QPropertyAnimation::DeleteWhenStopped);
    fadeWidget(dailyForecastWidget, 0, 450)->start(QPropertyAnimation::DeleteWhenStopped);
    fadeWidget(hourlyForecastWidget, 0, 450)->start(QPropertyAnimation::DeleteWhenStopped);
}

QPropertyAnimation* MainWindow::fadeWidget(QWidget* widget, int mode, int duration){ //0 - in, 1 - out
    QGraphicsOpacityEffect *widgetOpacity = new QGraphicsOpacityEffect(widget);
    widget->setGraphicsEffect(widgetOpacity);
    QPropertyAnimation *widgetOpacityAnimation = new QPropertyAnimation(widgetOpacity, "opacity");
    widgetOpacityAnimation->setDuration(duration);
    widgetOpacityAnimation->setStartValue(0);
    widgetOpacityAnimation->setEndValue(1);
    widgetOpacityAnimation->setEasingCurve(QEasingCurve::InBack);
    if (mode == 1)
        widgetOpacityAnimation->setDirection(QPropertyAnimation::Backward);
    return widgetOpacityAnimation;
}

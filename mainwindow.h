#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFontDatabase>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QObject>
#include <QGraphicsScene>
#include "weatherAPI.h"
#include "weatherwidget.h"
#include "dailyforecastwidget.h"
#include "hourlyforecastwidget.h"
#include "feelslikewidget.h"
#include "windwidget.h"
#include "sunwidget.h"
#include "datewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPropertyAnimation* fadeWidget(QWidget* widget, int mode, int duration);
private slots:
    void on_Exit_clicked();
    void dailyForecastLinePressed(int dayIndex);

private:
    Ui::MainWindow *ui;
    Weather* weather;
    HourlyForecastWidget* hourlyForecastWidget;
    DailyForecastWidget* dailyForecastWidget;
    FeelsLikeWidget* feelsLikeWidget;
    WindWidget* windWidget;
    SunWidget* sunWidget;
    DateWidget* dateWidget;

    void setupAttributes();
    void setupFonts();
    void animateFadingIn();
    void setupCurrentConditionsWidget();
    void adjustCurrentTemperatureFont();
    void fadeWidgetsIn();
    void msleep(int msec);

    QPropertyAnimation* widgetFadeAnimation(QGraphicsEffect* widgetGraphicsEffect, int duration, QEasingCurve easingCurve, QAbstractAnimation::Direction direction = QAbstractAnimation::Forward);
};
#endif // MAINWINDOW_H

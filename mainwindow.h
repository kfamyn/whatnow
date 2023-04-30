#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFontDatabase>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QSequentialAnimationGroup>
#include "weatherAPI.h"
#include "smoothscrollareawidget.h"

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
private:
    Ui::MainWindow *ui;
    Weather* weather;
    SmoothScrollAreaWidget* hourlyForecastWidget;
    SmoothScrollAreaWidget* dailyForecastWidget;

    void setupAttributes();
    void setupFonts();
    void animateFadingIn();
    void setupCurrentConditionsWidget();
    void adjustCurrentTemperatureFont();
    void fadeWidgetsIn();
    void msleep(int msec);
};
#endif // MAINWINDOW_H

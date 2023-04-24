#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <weatherAPI.h>
#include <smoothscrollareawidget.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void fadeWidget(QWidget* widget, int mode, int duration);
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
};
#endif // MAINWINDOW_H

#ifndef WINDWIDGET_H
#define WINDWIDGET_H

#include "informationwidget.h"
#include <QObject>
#include <QWidget>

const QString WIND_WIDGET_TEXT_STYLESHEET = "color: qconicalgradient(cx:1, cy:0, angle:270, stop:0 rgba(255, 255, 255, 255), stop:1 rgba(0, 0, 0, 255))";

class WindWidget : public InformationWidget
{
    Q_OBJECT
public:
    WindWidget(QWidget *parent = nullptr);
    void setup(Weather* weather) override;
public slots:
    void updateInfo(int dayIndex) final;
private:
    int windSpeed;
    qreal windDirection;
    QLabel* windSpeedLabel;
    QLabel* arrow;
    QLabel* compass;
    QLabel* south;
    QLabel* east;
    QLabel* north;
    QLabel* west;

    QLabel* createPixmapLabel(QString path, QSize size);
    QLabel* createTextLabel(QString text, QFont font, int fontSize, QFont::Weight weight,
                            QString styleSheet = WIND_WIDGET_TEXT_STYLESHEET, QSize labelSize = QSize(20, 20));
    QPoint cartesianToQPoint(int x, int y);
};

#endif // WINDWIDGET_H

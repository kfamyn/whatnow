#ifndef WINDWIDGET_H
#define WINDWIDGET_H

#include "informationwidget.h"
#include <QObject>
#include <QWidget>

const int ARROW_AMENDMENT = 1;

class WindWidget : public InformationWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal windDirection MEMBER m_windDirection WRITE setWindDirection )
public:
    WindWidget(QWidget *parent = nullptr);
    void setup(Weather* weather) override;
public slots:
    void updateInfo(int dayIndex) final;
private:
    int windSpeed;
    qreal m_windDirection;
    QLabel* windSpeedLabel;
    QLabel* arrow;
    QLabel* compass;
    QLabel* south;
    QLabel* east;
    QLabel* north;
    QLabel* west;
    void setWindDirection(qreal meteorologicalDegrees);

    QPoint cartesianToQPoint(int x, int y);
    QPoint qPointToCartesian(QPoint qPoint);
};

#endif // WINDWIDGET_H

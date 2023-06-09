#include "windwidget.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QtMath>

WindWidget::WindWidget(QWidget *parent) : InformationWidget(parent){
    windSpeed = 0;
    m_windDirection = 0;
    background = new QLabel(this);
    this->setBackground(":/background/assets/backgrounds/smallWidgetBackground.png", QSize(132, 132));
    this->setHeader("WIND");
    windSpeedLabel = createFixedSizeTextLabel("X M/S", 10, QFont::Normal, QSize(60, 16));
    arrow = createPixmapLabel(":/additionalWeatherIcons/assets/additionalWeatherIcons/sun.png", QSize(31, 31));
    compass = createPixmapLabel(":/additionalWeatherIcons/assets/additionalWeatherIcons/compass.png", QSize(88, 88));
    south = createFixedSizeTextLabel("S", 10, QFont::Normal);
    east = createFixedSizeTextLabel("E", 10, QFont::Normal);
    north = createFixedSizeTextLabel("N", 10, QFont::Normal);
    west = createFixedSizeTextLabel("W", 10, QFont::Normal);

    windSpeedLabel->move(39, 68);
    arrow->move(79, 26);
    compass->move(23, 32);
    south->move(57, 23);
    east->move(100, 66);
    north->move(57, 109);
    west->move(15, 66);
    this->arrow->raise();
}

void WindWidget::updateInfo(int dayIndex)
{
    int newWindSpeed = 0;
    qreal newWindDirection = 0;
    if (dayIndex == 0){
        newWindSpeed = std::stoi(weather->getCurrentConditions("windspeed"));
        newWindDirection = std::stoi(weather->getCurrentConditions("winddir"));
    }
    else {
        newWindSpeed = std::stoi(weather->getValue(dayIndex, "windspeed"));
        newWindDirection = std::stoi(weather->getValue(dayIndex, "winddir"));
    }
    QPropertyAnimation* windDirectionArrowAnimation = new QPropertyAnimation(this, "windDirection");
    int animationDuration = 200 + abs(m_windDirection - newWindDirection) * 3;
    windDirectionArrowAnimation->setDuration(animationDuration);
    windDirectionArrowAnimation->setStartValue(m_windDirection);
    windDirectionArrowAnimation->setEndValue(newWindDirection);
    windDirectionArrowAnimation->setEasingCurve(QEasingCurve::OutCubic);
    windDirectionArrowAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    windSpeed = newWindSpeed;
    m_windDirection = newWindDirection;
    this->windSpeedLabel->setText(QString::number(windSpeed).append(" M/S"));
}

QPoint WindWidget::cartesianToQPoint(int x, int y)
{
    return QPoint(x, this->parentWidget()->size().height() - y);
}

QPoint WindWidget::qPointToCartesian(QPoint qPoint)
{
    return QPoint(qPoint.x(), this->parentWidget()->size().height()-qPoint.y());
}

void WindWidget::setWindDirection(qreal meteorologicalDegrees) // to float!, to statics
{
    static float compassRadius = this->compass->size().width() / 2;
    static QPoint compassLeftUpperCornerQPointCoordinates = compass->pos();
    static QPoint compassCenterQPointCoordinates = QPoint(compassLeftUpperCornerQPointCoordinates.x() + compassRadius,
                                                          compassLeftUpperCornerQPointCoordinates.y() + compassRadius);
    static QPoint compassCenterCartesianCoordinates = qPointToCartesian(compassCenterQPointCoordinates);
    static float compassCenterCartesianX0 = compassCenterCartesianCoordinates.x();
    static float compassCenterCartesianY0 = compassCenterCartesianCoordinates.y();

    float meteorologicalToPolarDegrees = -meteorologicalDegrees + 90;
    float arrowCartesianX = compassCenterCartesianX0 + compassRadius * qCos(qDegreesToRadians(meteorologicalToPolarDegrees));
    float arrowCartesianY = compassCenterCartesianY0 + compassRadius * qSin(qDegreesToRadians(meteorologicalToPolarDegrees));

    float arrowLeftCornerCartesianX = arrowCartesianX - arrow->width() / 2 - ARROW_AMENDMENT;
    float arrowLeftCornerCartesianY = arrowCartesianY + arrow->height() / 2 + ARROW_AMENDMENT;

    this->arrow->move(cartesianToQPoint(arrowLeftCornerCartesianX, arrowLeftCornerCartesianY));
}

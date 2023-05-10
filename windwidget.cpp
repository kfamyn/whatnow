#include "windwidget.h"
#include <QFontDatabase>
#include <QPainter>
#include <QtMath>

WindWidget::WindWidget(QWidget *parent) : InformationWidget(parent){
    windSpeed = 0;
    m_windDirection = 0;
    background = new QLabel(this);
    this->setHeader("WIND");
    QFontDatabase::addApplicationFont(":/fonts/assets/Fonts/SFPro/SFProDisplay-Regular.ttf");
    QFont SFPro = QFont("SF Pro Display", 10, 0);
    windSpeedLabel = createTextLabel("X M/S", SFPro, 10, QFont::Normal, WIND_WIDGET_TEXT_STYLESHEET, QSize(60, 16));
    arrow = createPixmapLabel(":/additionalWeatherIcons/assets/additionalWeatherIcons/sun.png", QSize(31, 31));
    compass = createPixmapLabel(":/additionalWeatherIcons/assets/additionalWeatherIcons/compass.png", QSize(88, 88));
    south = createTextLabel("S", SFPro, 10, QFont::Normal);
    east = createTextLabel("E", SFPro, 10, QFont::Normal);
    north = createTextLabel("N", SFPro, 10, QFont::Normal);
    west = createTextLabel("W", SFPro, 10, QFont::Normal);

    windSpeedLabel->move(39, 68);
    arrow->move(79, 26);
    compass->move(23, 32);
    south->move(57, 23);
    east->move(100, 66);
    north->move(57, 109);
    west->move(15, 66);
}

void WindWidget::setup(Weather *weather)
{
    this->weather = weather;
    updateInfo(0);
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
    this->windSpeedLabel->setText(QString::number(newWindSpeed).append(" M/S"));
    setWindDirection(newWindDirection);
}

QLabel *WindWidget::createPixmapLabel(QString path, QSize size){
    QLabel* newLabel = new QLabel(this);
    newLabel->setFixedSize(size);
    newLabel->setPixmap(QPixmap(path));
    newLabel->setScaledContents(true);
    return newLabel;
}

QLabel *WindWidget::createTextLabel(QString text, QFont font, int fontSize, QFont::Weight weight, QString styleSheet, QSize labelSize)
{
    QLabel* textLabel = new QLabel(this);
    textLabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    textLabel->setText(text);
    font.setWeight(weight);
    font.setPointSize(fontSize);
    textLabel->setFont(font);
    textLabel->setStyleSheet(styleSheet);
    textLabel->setFixedSize(labelSize);
    return textLabel;
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
    this->arrow->raise();
}

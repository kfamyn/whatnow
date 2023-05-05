#include "feelslikewidget.h"
#include "format.hpp"
#include <QPropertyAnimation>

void FeelsLikeWidget::setup(Weather* weather)
{
    this->weather = weather;
    background = new QLabel(this);
    header = new QLabel(this);
    setupTemperatureLayout();
    QImage img(":/additionalWeatherIcons/assets/additionalWeatherIcons/thermometerMask.png");
    QBitmap mask = QBitmap::fromImage(img.scaled(100, 5, Qt::IgnoreAspectRatio, Qt::SmoothTransformation).createAlphaMask());
    thermometerWidget = new QWidget(this);
    thermometerWidget->move(16, 103);
    thermometerWidget->setMask(mask);
    temperatureScaleLabel = new QLabel(thermometerWidget);
    temperatureScaleLabel->setFixedSize(940, 35);
    temperatureScaleLabel->setPixmap(QPixmap(":/additionalWeatherIcons/assets/additionalWeatherIcons/temperatureGradient.png"));
    feelsLike = -35;
    updateThermometerWidget(0);
}

void FeelsLikeWidget::updateInfo(int day)
{
    this->temperatureLabel->setText(QString::fromStdString(formatTemperature(weather->getValue(day, "feelslike"))));
    updateThermometerWidget(day);
}

void FeelsLikeWidget::updateThermometerWidget(int dayIndex)
{
    int newFeelsLike = 0;
    if (dayIndex == 0){
        newFeelsLike = std::stoi(weather->getCurrentConditions("feelslike"));
    }
    else {
        newFeelsLike = std::stoi(weather->getValue(dayIndex, "feelslike"));
    }
    int degreesDelta = newFeelsLike - feelsLike;
    int pixelsDelta = -degreesDelta * 12;
    QPropertyAnimation* temperatureScaleLabelMoveAnimation = new QPropertyAnimation(temperatureScaleLabel, "pos");
    QPoint oldPosition = temperatureScaleLabel->pos();
    QPoint newPosition = QPoint(oldPosition.x() + pixelsDelta, oldPosition.y());
    temperatureScaleLabelMoveAnimation->setDuration(800);
    temperatureScaleLabelMoveAnimation->setStartValue(oldPosition);
    temperatureScaleLabelMoveAnimation->setEndValue(newPosition);
    temperatureScaleLabelMoveAnimation->setEasingCurve(QEasingCurve::OutCubic);
    temperatureScaleLabelMoveAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    feelsLike = newFeelsLike;
}

void FeelsLikeWidget::setupTemperatureLayout()
{
    QString temperature = QString::fromStdString(formatTemperature(weather->getCurrentConditions("feelslike")));
    leftSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
    temperatureLabel = createTextLabel(temperature, 37, QFont::Normal, "color: qconicalgradient(cx:1, cy:0, angle:273, stop:0 rgba(255, 255, 255, 255), stop:1 rgba(0, 0, 0, 255));", Qt::AlignTop | Qt::AlignRight);
    celciusLabel = createTextLabel("°C", 22, QFont::Normal, "color: qconicalgradient(cx:1, cy:0, angle:270, stop:0 rgba(255, 255, 255, 255), stop:1 rgba(0, 0, 0, 255));", Qt::AlignLeft | Qt::AlignTop);
    celciusLayout = new QVBoxLayout();
    celciusLayout->addWidget(celciusLabel);
    celciusLayout->setContentsMargins(0, 4, 0, 0);
    rightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);

    temperatureLayout = new QHBoxLayout(this);
    temperatureLayout->setSpacing(0);
    temperatureLayout->addSpacerItem(leftSpacer);
    temperatureLayout->addWidget(temperatureLabel);
    temperatureLayout->addLayout(celciusLayout);
    temperatureLayout->addSpacerItem(rightSpacer);
    temperatureLayout->setContentsMargins(0, 32, 0, 0);
}

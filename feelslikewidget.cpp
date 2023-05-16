#include "feelslikewidget.h"
#include <QPropertyAnimation>

FeelsLikeWidget::FeelsLikeWidget(QWidget *parent) : InformationWidget(parent){
    background = new QLabel(this);
    this->setHeader("FEELS LIKE");
    setupTemperatureLayout();
    QImage img(":/additionalWeatherIcons/assets/additionalWeatherIcons/thermometerMask.png");
    QBitmap mask = QBitmap::fromImage(img.scaled(100, 5, Qt::IgnoreAspectRatio, Qt::SmoothTransformation).createAlphaMask());
    thermometerWidget = new QWidget(this);
    thermometerWidget->move(16, 103);
    thermometerWidget->setMask(mask);
    temperatureScaleLabel = new QLabel(thermometerWidget);
    temperatureScaleLabel->setFixedSize(940, 35);
    temperatureScaleLabel->setPixmap(QPixmap(":/additionalWeatherIcons/assets/additionalWeatherIcons/temperatureGradient.png"));
    feelsLike = MIN_THERMOMETER_VISUALIZATION_TEMPERATURE;
}

void FeelsLikeWidget::setup(Weather* weather)
{
    this->weather = weather;
    updateInfo(0);
}

void FeelsLikeWidget::updateInfo(int dayIndex)
{
    int newFeelsLike = 0;
    if (dayIndex == 0){
        newFeelsLike = std::stoi(weather->getCurrentConditions("feelslike"));
    }
    else {
        newFeelsLike = std::stoi(weather->getValue(dayIndex, "feelslike"));
    }
    updateThermometerWidget(newFeelsLike);
    feelsLike = newFeelsLike;
    this->temperatureLabel->setText(QString::number(feelsLike));
}

void FeelsLikeWidget::updateThermometerWidget(int newFeelsLike)
{
    int degreesDelta;
    if (feelsLike >= MAX_THERMOMETER_VISUALIZATION_TEMPERATURE && newFeelsLike >= MAX_THERMOMETER_VISUALIZATION_TEMPERATURE){
        return;
    }
    else if (feelsLike <= MIN_THERMOMETER_VISUALIZATION_TEMPERATURE && newFeelsLike <= MIN_THERMOMETER_VISUALIZATION_TEMPERATURE){
        return;
    }
    if (newFeelsLike > MAX_THERMOMETER_VISUALIZATION_TEMPERATURE){
        degreesDelta = feelsLike - MAX_THERMOMETER_VISUALIZATION_TEMPERATURE;
    }
    else if (newFeelsLike < MIN_THERMOMETER_VISUALIZATION_TEMPERATURE){
        degreesDelta = feelsLike - MIN_THERMOMETER_VISUALIZATION_TEMPERATURE;
    }
    else {
        degreesDelta = feelsLike - newFeelsLike;
    }
    int pixelsDelta = degreesDelta * PIXELS_PER_DEGREE_IN_THERMOMETER;
    QPropertyAnimation* temperatureScaleLabelMoveAnimation = new QPropertyAnimation(temperatureScaleLabel, "pos");
    QPoint oldPosition = temperatureScaleLabel->pos();
    QPoint newPosition = QPoint(oldPosition.x() + pixelsDelta, oldPosition.y());
    temperatureScaleLabelMoveAnimation->setDuration(800);
    temperatureScaleLabelMoveAnimation->setStartValue(oldPosition);
    temperatureScaleLabelMoveAnimation->setEndValue(newPosition);
    temperatureScaleLabelMoveAnimation->setEasingCurve(QEasingCurve::OutCubic);
    temperatureScaleLabelMoveAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void FeelsLikeWidget::setupTemperatureLayout()
{
    leftSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
    temperatureLabel = createTextLabel("temperature", 37, QFont::Normal);
    temperatureLabel->setAlignment(Qt::AlignTop | Qt::AlignRight);
    celciusLabel = createTextLabel("°C", 22, QFont::Normal);
    celciusLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
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

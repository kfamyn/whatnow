#include "dailyforecastwidget.h"

DailyForecastWidget::DailyForecastWidget(QWidget* parent) {
    widgetSize = QSize(340, 324);
    this->setParent(parent);
    this->setFixedSize(widgetSize);
    background = new QLabel(this);
    background->setScaledContents(true);
    background->setFixedSize(widgetSize);
    forecastScrollArea = new DailyForecastScrollArea(this);
}

void DailyForecastWidget::setBackground(QString path){
    background->setPixmap(path);
    QImage img(path);
    QBitmap mask = QBitmap::fromImage(img.scaled(widgetSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation).createAlphaMask());
    forecastScrollArea->setMask(mask);
}

void DailyForecastWidget::setForecast(Weather& weather){
    forecastScrollArea->setup(weather);
}

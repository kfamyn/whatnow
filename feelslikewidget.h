#ifndef FEELSLIKEWIDGET_H
#define FEELSLIKEWIDGET_H

#include "informationwidget.h"
#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpacerItem>

const int MIN_THERMOMETER_VISUALIZATION_TEMPERATURE = -35;
const int MAX_THERMOMETER_VISUALIZATION_TEMPERATURE = 35;
const int PIXELS_PER_DEGREE_IN_THERMOMETER = 12;

class FeelsLikeWidget : public InformationWidget
{
    Q_OBJECT
public:
    FeelsLikeWidget(QWidget *parent = nullptr);
    void setup(Weather* weather) override;
public slots:
    void updateInfo(int dayIndex) final;
private:
    int feelsLike;
    QWidget* temperatureLayoutWidget;
    QHBoxLayout* temperatureLayout;
    QLabel* temperatureLabel;
    QVBoxLayout* celciusLayout;
    QLabel* celciusLabel;
    QSpacerItem* leftSpacer;
    QSpacerItem* rightSpacer;
    QLabel* temperatureScaleLabel;
    QWidget* thermometerWidget;

    void updateThermometerWidget(int newFeelsLike);
    void setupTemperatureLayout();
};

#endif // FEELSLIKEWIDGET_H

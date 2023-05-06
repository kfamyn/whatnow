#ifndef FEELSLIKEWIDGET_H
#define FEELSLIKEWIDGET_H

#include "informationwidget.h"
#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpacerItem>

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

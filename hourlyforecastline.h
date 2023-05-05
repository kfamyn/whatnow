#ifndef HOURLYFORECASTLINE_H
#define HOURLYFORECASTLINE_H

#include <QWidget>
#include <QLabel>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFont>
#include <QFontDatabase>

class HourlyForecastLine : public QWidget
{
    Q_OBJECT
public:
    HourlyForecastLine(QWidget* parent);
    void setup(QString date, QString time, QString iconURL, QString precipitationProbability, QString temperature);
    void fill(QString date, QString time, QString iconURL, QString precipitationProbability, QString temperature);
private:
    QLabel* createTextLabel(QString text, int fontSize, QFont::Weight weight, QString styleSheet, Qt::Alignment alignment, QSizePolicy::Policy policy1 = QSizePolicy::Preferred, QSizePolicy::Policy policy2 = QSizePolicy::Preferred);
    QLabel* createIconLabel(QString iconURL, int size);
    void setupPrecipitationProbabilityLayout(QString precipitationProbability);
    void setupTemperatureLayout(QString temperature);
    void setupHourlyForecastLayout();

    QLabel* dateLabel;
    QLabel* timeLabel;
    QSpacerItem* iconVerticalSpacer;
    QLabel* weatherIconLabel;
    QHBoxLayout* precipitationProbabilityLayout;
    QSpacerItem* precipitationProbabilityLeftSpacer;
    QLabel* precipitationProbabilityLabel;
    QVBoxLayout* precipitationIconLayout;
    QLabel* precipitationIconLabel;
    QSpacerItem* precipitationProbabilityRightSpacer;
    QHBoxLayout* temperatureLayout;
    QSpacerItem* temperatureLeftSpacer;
    QLabel* temperatureLabel;
    QVBoxLayout* celciusLayout;
    QLabel* celciusLabel;
    QSpacerItem* temperatureRightSpacer;
    QVBoxLayout* hourlyForecastLayout;
};

#endif // HOURLYFORECASTLINE_H

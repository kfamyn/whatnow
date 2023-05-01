#ifndef DAILYFORECASTLINE_H
#define DAILYFORECASTLINE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QLabel>
#include <QFont>
#include <QFontDatabase>
#include <QEvent>
#include <QObject>

class DailyForecastLine : public QWidget
{
    Q_OBJECT
public:
    DailyForecastLine(QWidget* parent);
    void setup(QString iconURL, QString temperatureDay, QString temperatureNight, QString dayOfWeek, int index);
    void fill(QString iconURL, QString temperatureDay, QString temperatureNight, QString dayOfWeek);
signals:
    void linePressed(int lineIndex);
private:
    int index;
    QHBoxLayout *forecastLayout;
    QLabel *iconLabel;
    QLabel *temperatureLabelDay;
    QLabel *temperatureLabelNight;
    QLabel *dayOfWeekLabel;
    QLabel *slashLabel;
    QLabel *celciusLabelDay;
    QLabel *celciusLabelNight;
    QLabel *plainTextDay;
    QLabel *plainTextNight;
    QHBoxLayout *temperatureLayout;
    QHBoxLayout *temperatureLayoutDay;
    QVBoxLayout *celciusLayoutDay;
    QHBoxLayout *temperatureLayoutNight;
    QVBoxLayout *celciusLayoutNight;

    QLabel* createQLabel(QString text,QFont& font, int fontSize, QFont::Weight weight, float gradientStop, Qt::Alignment alignment, QSizePolicy::Policy policy1 = QSizePolicy::Preferred, QSizePolicy::Policy policy2 = QSizePolicy::Preferred);
    bool eventFilter(QObject *object, QEvent *event);
};

#endif // DAILYFORECASTLINE_H

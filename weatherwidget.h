#ifndef WEATHERWIDGET_H
#define WEATHERWIDGET_H

#include "smoothscrollarea.h"
#include "hourlyforecastline.h"
#include "weatherAPI.h"
#include "dailyforecastline.h"
#include <QLabel>
#include <QVector>

template <typename typeOfContents>
class WeatherWidget : public QWidget
{
public:
    explicit WeatherWidget(QWidget *parent = nullptr);
    void setBackground(QString path, QSize size);
    typeOfContents* getLine(int index);
    QWidget* getWidgetContents();
protected:
    Weather* weather;
    QLabel* background;
    QVector<typeOfContents*> forecastLines;
    QWidget* scrollAreaWidgetContents;
    SmoothScrollArea* widgetScrollarea;
};

template<typename typeOfContents>
WeatherWidget<typeOfContents>::WeatherWidget(QWidget *parent)
    : QWidget{parent}
{}

template<typename typeOfContents>
void WeatherWidget<typeOfContents>::setBackground(QString path, QSize size)
{
    this->setFixedSize(size);
    background->setScaledContents(true);
    background->setFixedSize(size);
    background->setPixmap(path);
    QImage img(path);
    QBitmap mask = QBitmap::fromImage(img.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation).createAlphaMask());
    widgetScrollarea->setMask(mask);
}

template<typename typeOfContents>
typeOfContents* WeatherWidget<typeOfContents>::getLine(int index)
{
    return forecastLines[index];
}

template<typename typeOfContents>
QWidget *WeatherWidget<typeOfContents>::getWidgetContents()
{
    return scrollAreaWidgetContents;
}

#endif // WEATHERWIDGET_H

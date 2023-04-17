#include "dailyforecastscrollarea.h"
#include "dailyforecastline.h"
#include "format.hpp"
#include "qpropertyanimation.h"
#include "qscrollbar.h"

DailyForecastScrollArea::DailyForecastScrollArea(QWidget* parent)
{
    this->setParent(parent);
    this->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    this->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    this->setWidgetResizable(true);
    this->setGeometry(0, 0, 340, 323);
}

void DailyForecastScrollArea::setForecast(Weather &weather)
{
    QWidget* scrollAreaWidgetContents = new QWidget(this);
    this->setWidget(scrollAreaWidgetContents);
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollAreaWidgetContents);
    for (int index = 0; index < 14; ++index) {
        QString iconURL = ":/weatherIcons/assets/weatherIcons/";
        iconURL += QString::fromStdString(weather.getValue(index, "icon"));
        iconURL += ".png";
        QString temperatureDay = QString::number(std::stoi(weather.getValue(index, "tempmax")));
        QString temperatureNight = QString::number(std::stoi(weather.getValue(index, "tempmin")));
        QString date = QString::fromStdString(weather.getValue(index, "datetime"));
        int year = date.mid(0, 4).toInt();
        int month = date.mid(5,2).toInt();
        int day = date.mid(8,2).toInt();
        QString dayOfWeek = QString::fromStdString(formatDayOfWeek(year, month, day));
        DailyForecastLine* forecastLine = new DailyForecastLine(iconURL, temperatureDay, temperatureNight, dayOfWeek);
        scrollLayout->addWidget(forecastLine);
    }
    scrollAreaWidgetContents->setStyleSheet("background-color:transparent;");
    this->verticalScrollBar()->setStyle(new QCommonStyle);
    this->verticalScrollBar()->setSingleStep(7);
    this->setStyleSheet("QScrollArea {"
                        "background-color:transparent;"
                        "border:none"
                        "}"
                        "        /* VERTICAL */"
                        "        QScrollBar:vertical {"
                        "            border: 0px solid #999999;"
                        "            background:transparent;"
                        "            width:7px;    "
                        "            margin: 28px 3px 28px 0px;"
                        "        }"
                        "        QScrollBar::handle:vertical {  "
                        "            min-height: 0px;"
                        "            border: 0px solid red;"
                        "            border-radius: 2px;"
                        "            background-color: rgb(62, 41, 112);"
                        "        }"
                        "        QScrollBar::add-line:vertical {       "
                        "            height: 0px;"
                        "            subcontrol-position: bottom;"
                        "            subcontrol-origin: margin;"
                        "        }"
                        "        QScrollBar::sub-line:vertical {"
                        "            height: 0 px;"
                        "            subcontrol-position: top;"
                        "            subcontrol-origin: margin;"
                        "        }"
                        "        QScrollBar::handle:vertical:hover { "
                        "        background-color: rgb(35, 25, 66);"
                        "        }"
                        );
}

bool DailyForecastScrollArea::eventFilter(QObject *object, QEvent *event){
    if (event->type() == QEvent::Wheel) {
        QWheelEvent* wheelEvent = static_cast<QWheelEvent *>(event);
        QPoint numPixels = wheelEvent->angleDelta();
        QPropertyAnimation* smoothScrollingAnimation = new QPropertyAnimation(this->verticalScrollBar(), "value");
        int endValue = calculateEndScrollBarValue(numPixels.y());
        smoothScrollingAnimation->setDuration(240);
        smoothScrollingAnimation->setStartValue(this->verticalScrollBar()->value());
        smoothScrollingAnimation->setEndValue(endValue);
        smoothScrollingAnimation->setEasingCurve(QEasingCurve::OutCubic);
        smoothScrollingAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        return true;
    }
    return QObject::eventFilter(object, event);
}

int DailyForecastScrollArea::calculateEndScrollBarValue(int delta){
    int estimatedEndValue = this->verticalScrollBar()->value() - delta;
    int endValue = estimatedEndValue;
    if (estimatedEndValue >= this->verticalScrollBar()->maximum()){
        endValue = this->verticalScrollBar()->maximum();
    }
    else if(estimatedEndValue <= 0){
        endValue = 0;
    }
    return endValue;
}

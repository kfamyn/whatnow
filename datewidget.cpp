#include "datewidget.h"
#include "format.hpp"

DateWidget::DateWidget(QWidget *parent) : InformationWidget(parent)
{
    background = new QLabel(this);
    this->setBackground(":/background/assets/backgrounds/calendarWidgetBackground.png", QSize(280, 280));
    conditions = createFixedSizeTextLabel("conditions", 12, QFont::Normal, QSize(background->size().width(), 31));
    conditions->move(0, 10);
    conditions->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    date = createFixedSizeTextLabel("1", 139, QFont::Normal, QSize(280, 160));
    date->move(0, 56);
    month = createFixedSizeTextLabel("JAN", 16, QFont::Normal, QSize(280, 31));
    month->move(0, 225);
}

void DateWidget::updateInfo(int dayIndex)
{
    QString conditionsText = "";
    QString dateText = "";
    QString monthText = "";
    if (dayIndex == 0){
        conditionsText = QString::fromStdString(weather->getCurrentConditions("conditions"));
    }
    else {
        conditionsText = QString::fromStdString(weather->getValue(dayIndex, "conditions"));
    }
    dateText = QString::fromStdString(formatDate(weather->getValue(dayIndex, "datetime")));
    monthText = dateText.mid(dateText.length() - 3);
    dateText = dateText.mid(0, dateText.length() - 3);
    conditions->setText(conditionsText);
    date->setText(dateText);
    month->setText(monthText);
}

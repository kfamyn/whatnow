#ifndef DATEWIDGET_H
#define DATEWIDGET_H

#include "informationwidget.h"
#include <QObject>
#include <QWidget>

class DateWidget : public InformationWidget
{
    Q_OBJECT
public:
    DateWidget(QWidget *parent = nullptr);
public slots:
    void updateInfo(int dayIndex) final;
private:
    QLabel* conditions;
    QLabel* date;
    QLabel* month;
};

#endif // DATEWIDGET_H

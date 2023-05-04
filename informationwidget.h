#ifndef INFORMATIONWIDGET_H
#define INFORMATIONWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include "weatherAPI.h"

class InformationWidget : public QWidget
{
    Q_OBJECT
public:
    InformationWidget(QWidget *parent = nullptr) : QWidget(parent){};
    void setBackground(QString path, QSize size);
    virtual void setHeader(QString text);
    virtual void setup(Weather* weather) = 0;
public slots:
    virtual void updateInfo(int day) = 0;
protected:
    Weather* weather;
    QLabel* background;
    QLabel* header;

    QLabel* createTextLabel(QString text, int fontSize, QFont::Weight weight, QString styleSheet, Qt::Alignment alignment, QSizePolicy::Policy policy1 = QSizePolicy::Preferred, QSizePolicy::Policy policy2 = QSizePolicy::Preferred);
};

#endif // INFORMATIONWIDGET_H

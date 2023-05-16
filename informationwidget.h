#ifndef INFORMATIONWIDGET_H
#define INFORMATIONWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include "weatherAPI.h"

const QString DEFAULT_STYLESHEET = "color: qconicalgradient(cx:1, cy:0, angle:270, stop:0 rgba(255, 255, 255, 255), stop:1 rgba(0, 0, 0, 255))";

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

    QLabel* createPixmapLabel(QString path, QSize size);
    QLabel* createFixedSizeTextLabel(QString text, QFont font, int fontSize, QFont::Weight weight,
                            QSize labelSize = QSize(20, 20), QString styleSheet = DEFAULT_STYLESHEET);
    QLabel* createTextLabel(QString text, QFont font, int fontSize, QFont::Weight weight,
                            QString styleSheet = DEFAULT_STYLESHEET);
};

#endif // INFORMATIONWIDGET_H

#ifndef SMOOTHSCROLLAREA_H
#define SMOOTHSCROLLAREA_H

#include <QObject>
#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCommonStyle>
#include <QScrollBar>
#include <QEvent>
#include <QWheelEvent>
#include <QPropertyAnimation>
#include <QScrollBar>

class SmoothScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    SmoothScrollArea(QWidget* parent);
    enum orientations {VERTICAL = 0, HORIZONTAL = 1};
    void setup();
    void setupContents(QWidget* contentsLayout, orientations orientation);
private:
    orientations orientation;
    bool eventFilter(QObject *object, QEvent *event) override;
    int calculateEndScrollBarValue(int delta, QScrollBar* scrollBar);
    QPropertyAnimation* smoothScrollingAnimation = NULL;
};

#endif // SMOOTHSCROLLAREA_H

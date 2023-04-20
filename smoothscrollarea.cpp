#include "smoothscrollarea.h"

SmoothScrollArea::SmoothScrollArea(QWidget *parent): QScrollArea(parent){}

void SmoothScrollArea::setup()
{
    orientation = VERTICAL;
    this->setWidgetResizable(true);
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
                        "        /* HORIZONTAL */"
                        "        QScrollBar:horizontal {"
                        "            border: 0px solid #999999;"
                        "            background:transparent;"
                        "            width:7px;    "
                        "            margin: 28px 3px 28px 0px;"
                        "        }"
                        "        QScrollBar::handle:horizontal {  "
                        "            min-height: 0px;"
                        "            border: 0px solid red;"
                        "            border-radius: 2px;"
                        "            background-color: rgb(62, 41, 112);"
                        "        }"
                        "        QScrollBar::add-line:horizontal {       "
                        "            height: 0px;"
                        "            subcontrol-position: bottom;"
                        "            subcontrol-origin: margin;"
                        "        }"
                        "        QScrollBar::sub-line:horizontal {"
                        "            height: 0 px;"
                        "            subcontrol-position: top;"
                        "            subcontrol-origin: margin;"
                        "        }"
                        "        QScrollBar::handle:horizontal:hover { "
                        "        background-color: rgb(35, 25, 66);"
                        "        }"
                        );
}

void SmoothScrollArea::setupContents(QWidget *contentsLayout, orientations orientation)
{
    this->orientation = orientation;
    //this->setGeometry(0, 0, 340, 323); // !!!!!!!!!!!!!!!!!!
    this->setVerticalScrollBarPolicy( orientation == VERTICAL ? Qt::ScrollBarAlwaysOn : Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy( orientation == VERTICAL ? Qt::ScrollBarAlwaysOff : Qt::ScrollBarAlwaysOn);
    this->setWidget(contentsLayout);
    this->verticalScrollBar()->setStyle(new QCommonStyle);
    this->verticalScrollBar()->setSingleStep(7);
    this->horizontalScrollBar()->setStyle(new QCommonStyle);
    this->horizontalScrollBar()->setSingleStep(7);
}

bool SmoothScrollArea::eventFilter(QObject *object, QEvent *event){
    if (event->type() == QEvent::Wheel) {
        QWheelEvent* wheelEvent = static_cast<QWheelEvent *>(event);
        QPoint numPixels = wheelEvent->angleDelta();
        QScrollBar* scrollBar = orientation == VERTICAL ? verticalScrollBar() : horizontalScrollBar();
        QPropertyAnimation* smoothScrollingAnimation = new QPropertyAnimation(scrollBar, "value");
        int endValue = calculateEndScrollBarValue(numPixels.y(), scrollBar);
        smoothScrollingAnimation->setDuration(240);
        smoothScrollingAnimation->setStartValue(scrollBar->value());
        smoothScrollingAnimation->setEndValue(endValue);
        smoothScrollingAnimation->setEasingCurve(QEasingCurve::OutCubic);
        smoothScrollingAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        return true;
    }
    return QObject::eventFilter(object, event);
}

int SmoothScrollArea::calculateEndScrollBarValue(int delta, QScrollBar* scrollBar){
    int estimatedEndValue = scrollBar->value() - delta;
    int endValue = estimatedEndValue;
    if (estimatedEndValue >= scrollBar->maximum()){
        endValue = scrollBar->maximum();
    }
    else if(estimatedEndValue <= 0){
        endValue = 0;
    }
    return endValue;
}

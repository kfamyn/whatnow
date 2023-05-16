#include "informationwidget.h"
#include <QFontDatabase>

void InformationWidget::setBackground(QString path, QSize size)
{
    this->setFixedSize(size);
    background->setScaledContents(true);
    background->setFixedSize(size);
    background->setPixmap(path);
    QImage img(path);
    QBitmap mask = QBitmap::fromImage(img.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation).createAlphaMask());
    this->setMask(mask);
}

void InformationWidget::setHeader(QString text)
{
    header = new QLabel(this);
    header->setText(text);
    header->setFixedSize(101, 16);
    header->setStyleSheet("color: qconicalgradient(cx:1, cy:0, angle:270, stop:0 rgba(255, 255, 255, 255), stop:1 rgba(0, 0, 0, 255))");
    QFontDatabase::addApplicationFont(":/fonts/assets/Fonts/SFPro/SFProDisplay-Regular.ttf");
    QFont SFProLight10 = QFont("SF Pro Display", 10, 0);
    SFProLight10.setWeight(QFont::Normal);
    header->setFont(SFProLight10);
    header->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    header->setMargin(2);
    header->move(14, 11);
}

QLabel *InformationWidget::createPixmapLabel(QString path, QSize size){
    QLabel* newLabel = new QLabel(this);
    newLabel->setFixedSize(size);
    newLabel->setPixmap(QPixmap(path));
    newLabel->setScaledContents(true);
    return newLabel;
}

QLabel *InformationWidget::createTextLabel(QString text, QFont font, int fontSize, QFont::Weight weight, QString styleSheet)
{
    QLabel* textLabel = new QLabel(this);
    textLabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    textLabel->setText(text);
    font.setWeight(weight);
    font.setPointSize(fontSize);
    textLabel->setFont(font);
    textLabel->setStyleSheet(styleSheet);
    return textLabel;
}

QLabel *InformationWidget::createFixedSizeTextLabel(QString text, QFont font, int fontSize, QFont::Weight weight, QSize labelSize, QString styleSheet)
{
    QLabel* textLabel = createTextLabel(text, font, fontSize, weight, styleSheet);
    textLabel->setFixedSize(labelSize);
    return textLabel;
}

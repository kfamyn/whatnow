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
    header = createFixedSizeTextLabel(text, 10, QFont::Normal, QSize(101, 16));
    header->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    header->setMargin(2);
    header->move(14, 11);
}

void InformationWidget::setup(Weather* weather)
{
    this->weather = weather;
    updateInfo(0);
}

QLabel *InformationWidget::createPixmapLabel(QString path, QSize size){
    QLabel* newLabel = new QLabel(this);
    newLabel->setFixedSize(size);
    newLabel->setPixmap(QPixmap(path));
    newLabel->setScaledContents(true);
    return newLabel;
}

QLabel *InformationWidget::createTextLabel(QString text, int fontSize, QFont::Weight weight, QString styleSheet)
{
    QFontDatabase::addApplicationFont(":/fonts/assets/Fonts/SFPro/SFProDisplay-Regular.ttf");
    static QFont SFPro = QFont("SF Pro Display", 10, 0);
    QLabel* textLabel = new QLabel(this);
    textLabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    textLabel->setText(text);
    SFPro.setWeight(weight);
    SFPro.setPointSize(fontSize);
    textLabel->setFont(SFPro);
    textLabel->setStyleSheet(styleSheet);
    return textLabel;
}

QLabel *InformationWidget::createFixedSizeTextLabel(QString text, int fontSize, QFont::Weight weight, QSize labelSize, QString styleSheet)
{
    QLabel* textLabel = createTextLabel(text, fontSize, weight, styleSheet);
    textLabel->setFixedSize(labelSize);
    return textLabel;
}

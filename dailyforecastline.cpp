#include "dailyforecastline.h"

DailyForecastLine::DailyForecastLine(QWidget* parent): QWidget(parent) {
    this->setFixedSize(317, 50);
    QFontDatabase::addApplicationFont(":/fonts/assets/Fonts/SFPro/SFProDisplay-Regular.ttf");
    QFont SFPro = QFont("SF Pro Display", 22, 0);
    setupIconLabel("iconURL");
    temperatureLabelDay = createQLabel("temperatureDay", SFPro, 22, QFont::DemiBold, 0.9, Qt::AlignVCenter | Qt::AlignRight);
    temperatureLabelDay->setMinimumSize(45, 46);
    celciusLabelDay = createQLabel("°C", SFPro, 14, QFont::Normal, 0.6, Qt::AlignVCenter | Qt::AlignLeft);
    setupCelciusLayoutDay();
    setupTemperatureLayoutDay();
    slashLabel = createQLabel("/", SFPro, 17, QFont::Normal, 0.3, Qt::AlignVCenter | Qt::AlignCenter);
    temperatureLabelNight = createQLabel("temperatureNight", SFPro, 17, QFont::DemiBold, 0.3, Qt::AlignVCenter | Qt::AlignLeft, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    celciusLabelNight = createQLabel("°C", SFPro, 12, QFont::Normal, 0.6, Qt::AlignVCenter | Qt::AlignLeft);
    setupCelciusLabelNight();
    setupTemperatureLayoutNight();
    setupTemperatureLayout();
    dayOfWeekLabel = createQLabel("dayOfWeek", SFPro, 14, QFont::Normal, 0.9, Qt::AlignVCenter | Qt::AlignCenter, QSizePolicy::Fixed, QSizePolicy::Fixed);
    dayOfWeekLabel->setFixedSize(105, 50);
    setupForecastLayout();
    this->installEventFilter(this);
};

void DailyForecastLine::fill(QString iconURL, QString temperatureDay, QString temperatureNight, QString dayOfWeek)
{
    iconLabel->setPixmap(QPixmap(iconURL));
    temperatureLabelDay->setText(temperatureDay);
    temperatureLabelNight->setText(temperatureNight);
    dayOfWeekLabel->setText(dayOfWeek);
}

int& DailyForecastLine::getIndex()
{
    return index;
}

QLabel* DailyForecastLine::createQLabel(QString text, QFont& font, int fontSize, QFont::Weight weight, float gradientStop, Qt::Alignment alignment, QSizePolicy::Policy policy1, QSizePolicy::Policy policy2){
    QLabel* label = new QLabel(this);
    label->setText(text);
    font.setPointSize(fontSize);
    font.setWeight(weight);
    label->setFont(font);
    label->setSizePolicy(policy1, policy2);
    QString styleSheet = "color: qconicalgradient(cx:0.5, cy:0.5, angle:0, stop:0 rgba(255,255,255,0), stop:";
    styleSheet.append(QString::number(gradientStop));
    styleSheet.append(" rgba(255,255,255,255),  stop:1 rgba(202, 162, 203, 255));");
    label->setStyleSheet(styleSheet);
    label->setAlignment(alignment);
    return label;
}

bool DailyForecastLine::eventFilter(QObject *object, QEvent *event){
    if (event->type() == QEvent::MouseButtonPress){
        emit linePressed(index);
    }
    return QObject::eventFilter(object, event);
}

void DailyForecastLine::setupIconLabel(QString iconURL)
{
    iconLabel = new QLabel(this);
    iconLabel->setPixmap(QPixmap(iconURL));
    iconLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    iconLabel->setFixedSize(50, 50);
    iconLabel->setScaledContents(true);
    iconLabel->setAlignment(Qt::AlignVCenter | Qt::AlignCenter);
}

void DailyForecastLine::setupCelciusLayoutDay()
{
    celciusLayoutDay = new QVBoxLayout();
    celciusLayoutDay->setSpacing(0);
    celciusLayoutDay->addWidget(celciusLabelDay);
    celciusLayoutDay->setContentsMargins(0, 0, 0, 10);
}

void DailyForecastLine::setupTemperatureLayoutDay()
{
    temperatureLayoutDay = new QHBoxLayout();
    temperatureLayoutDay->setSpacing(0);
    temperatureLayoutDay->addWidget(temperatureLabelDay);
    temperatureLayoutDay->addLayout(celciusLayoutDay);
}

void DailyForecastLine::setupCelciusLabelNight()
{
    celciusLayoutNight = new QVBoxLayout();
    celciusLayoutNight->setSpacing(0);
    celciusLayoutNight->addWidget(celciusLabelNight);
    celciusLayoutNight->setContentsMargins(0, 0, 0, 8);
}

void DailyForecastLine::setupTemperatureLayoutNight()
{
    temperatureLayoutNight = new QHBoxLayout();
    temperatureLayoutNight->setSpacing(0);
    temperatureLayoutNight->setContentsMargins(5, 0, 0, 0);
    temperatureLayoutNight->addWidget(temperatureLabelNight);
    temperatureLayoutNight->addLayout(celciusLayoutNight);
    temperatureLayoutNight->setStretch(0, 1);
    temperatureLayoutNight->setStretch(1, 9);
}

void DailyForecastLine::setupTemperatureLayout()
{
    temperatureLayout = new QHBoxLayout();
    temperatureLayout->setSpacing(0);
    temperatureLayout->addLayout(temperatureLayoutDay);
    temperatureLayout->addWidget(slashLabel);
    temperatureLayout->addLayout(temperatureLayoutNight);
}

void DailyForecastLine::setupForecastLayout()
{
    forecastLayout = new QHBoxLayout(this);
    forecastLayout->setSpacing(2);
    forecastLayout->setContentsMargins(12, 0, 0, 0);
    forecastLayout->setStretch(0, 0);
    forecastLayout->setStretch(1, 0);
    forecastLayout->setStretch(2, 1);
    forecastLayout->addWidget(iconLabel);
    forecastLayout->addLayout(temperatureLayout);
    forecastLayout->addWidget(dayOfWeekLabel);
}

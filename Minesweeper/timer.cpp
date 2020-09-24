#include "timer.h"

Timer::Timer(QWidget *parent) : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);

    mTimer = new QTimer(this);

    connect(mTimer, &QTimer::timeout, this, &Timer::addSecond);

    auto label = new QLabel("Zeit vergangen:", this);
    mTimerLabel = new QLabel("00:00", this);

    label->setAlignment(Qt::AlignHCenter);
    mTimerLabel->setAlignment(Qt::AlignHCenter);

    layout->addWidget(label);
    layout->addWidget(mTimerLabel);

    // Layout anwenden -> bereits bei initialisierung geschehen
    // this->setLayout(layout);
}

void Timer::startTimer()
{
    mTimer->start(1000);
}

void Timer::stopTimer()
{
    mTimer->stop();
}

void Timer::addSecond()
{
    if(!(++mSeconds %= 60))
    {
        ++mMinutes;
    }

    QString text = QString("%1:%2").arg(QString::number(mMinutes), 2, '0').arg(QString::number(mSeconds), 2, '0');

    mTimerLabel->setText(text);
}

void Timer::resetTimer()
{
    stopTimer();

    mSeconds = 0;
    mMinutes = 0;

    mTimerLabel->setText("00:00");
}

#include "timer.h"

// Constructor
Timer::Timer(QWidget *parent) : QWidget(parent)
{
    // Layout erstellen
    auto layout = new QVBoxLayout(this);

    // Timer erstellen
    mTimer = new QTimer(this);

    // Signale und Slots verbinden
    connect(mTimer, &QTimer::timeout, this, &Timer::addSecond);

    // Labels erstellen
    auto label = new QLabel("Zeit vergangen:", this);
    mTimerLabel = new QLabel("00:00", this);

    // Labelausrichtung festlegen
    label->setAlignment(Qt::AlignHCenter);
    mTimerLabel->setAlignment(Qt::AlignHCenter);

    // Labels zu Layout hinzufügen
    layout->addWidget(label);
    layout->addWidget(mTimerLabel);
}

// Timer starten (1 Sekunde)
void Timer::startTimer()
{
    mTimer->start(1000);
}

// Timer anhalten
void Timer::stopTimer()
{
    mTimer->stop();
}

// Sekunde hinzufügen
void Timer::addSecond()
{
    if(!(++mSeconds %= 60))
    {
        ++mMinutes;
    }

    QString text = QString("%1:%2").arg(mMinutes, 2, 10, QLatin1Char('0')).arg(mSeconds, 2, 10, QLatin1Char('0'));

    mTimerLabel->setText(text);
}

// Timer zurücksetzen
void Timer::resetTimer()
{
    stopTimer();

    mSeconds = 0;
    mMinutes = 0;

    mTimerLabel->setText("00:00");
}

unsigned int Timer::minutes() const
{
    return mMinutes;
}

unsigned int Timer::seconds() const
{
    return mSeconds;
}

unsigned int Timer::totalSeconds() const
{
    return mMinutes * 60 + mSeconds;
}

#ifndef TIMER_H
#define TIMER_H

#include <QWidget>
#include <QBoxLayout>
#include <QTimer>
#include <QLabel>

class Timer : public QWidget
{
    Q_OBJECT
public:
    explicit Timer(QWidget *parent = nullptr);

    void addSecond();   // -> private?
    void resetTimer();

    // Get und Set Funktionen
    unsigned int minutes() const;
    unsigned int seconds() const;
    unsigned int totalSeconds() const;

public slots:
    void startTimer();
    void stopTimer();

signals:

private:
    QTimer* mTimer = nullptr;
    QLabel* mTimerLabel = nullptr;

    unsigned int mMinutes = 0;
    unsigned int mSeconds = 0;
};

#endif // TIMER_H

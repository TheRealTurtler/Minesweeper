#ifndef BEST_TIME_H
#define BEST_TIME_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QDir>

#include <QDebug>

class BestTime : public QWidget
{
    Q_OBJECT
public:
    explicit BestTime(QWidget *parent = nullptr);

    void displayBestTime(unsigned int columns, unsigned int rows, unsigned int mines);
    void saveBestTime(unsigned int columns, unsigned int rows, unsigned int mines, unsigned int minutes, unsigned int seconds);

    // Get und Set Funktionen
    unsigned int minutes() const;
    unsigned int seconds() const;
    unsigned int totalSeconds() const;
    bool available() const;

signals:

private:
    QLabel* mBestTimeLabel;

    unsigned int mMinutes;
    unsigned int mSeconds;

    bool mBestTimeAvailable = false;
};

#endif // BEST_TIME_H

#ifndef MINE_COUNTER_H
#define MINE_COUNTER_H

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>

class MineCounter : public QWidget
{
    Q_OBJECT
public:
    explicit MineCounter(QWidget *parent = nullptr);

public slots:
    void displayRemainingMines(const int remainingMines);

signals:

private:
    QLabel* mCounterLabel = nullptr;
};

#endif // MINECOUNTER_H

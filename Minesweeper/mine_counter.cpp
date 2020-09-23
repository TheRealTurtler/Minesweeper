#include "mine_counter.h"

MineCounter::MineCounter(QWidget *parent) : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);

    auto label = new QLabel("Mines remaining:", this);
    mCounterLabel = new QLabel("0", this);

    label->setAlignment(Qt::AlignHCenter);
    mCounterLabel->setAlignment(Qt::AlignHCenter);

    layout->addWidget(label);
    layout->addWidget(mCounterLabel);

    // Layout anwenden -> bereits bei initialisierung geschehen
    // this->setLayout(layout);
}

void MineCounter::displayRemainingMines(const int remainingMines)
{
    mCounterLabel->setText(QString::number(remainingMines));
}

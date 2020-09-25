#include "mine_counter.h"

// Constructor
MineCounter::MineCounter(QWidget *parent) : QWidget(parent)
{
    //Layout erstellen
    auto layout = new QVBoxLayout(this);

    // Labels erstellen
    auto label = new QLabel("Mienen verbleibend:", this);
    mCounterLabel = new QLabel("0", this);

    // Labelausrichtuing festlegen
    label->setAlignment(Qt::AlignHCenter);
    mCounterLabel->setAlignment(Qt::AlignHCenter);

    // Labels zu Layout hinzufügen
    layout->addWidget(label);
    layout->addWidget(mCounterLabel);
}

// Verbleibende Mienen anzeigen
void MineCounter::displayRemainingMines(const int remainingMines)
{
    mCounterLabel->setText(QString::number(remainingMines));
}

#include "interface.h"

Interface::Interface(QWidget *parent, QStatusBar* statusBar) : QWidget(parent), mStatusBar(statusBar)
{
    auto layoutH = new QHBoxLayout;
    auto layoutV1 = new QVBoxLayout(this);
    auto layoutV2 = new QVBoxLayout;

    // Spiel erstellen
    auto game = new Game(9, 9, 10, this);           // Einfach 9x9 mit 10 Mienen
    //auto game = new Game(16, 16, 40, this);           // Fortgeschritten 16x16 mit 40 Mienen
    //auto game = new Game(30, 16, 99, this);         // Experte 30x16 mit 99 Mienen

    auto timer = new Timer(this);

    auto mineCounter = new MineCounter(this);

    connect(game, &Game::gameStarted, timer, &Timer::startTimer);
    connect(game, &Game::gameFinished, timer, &Timer::stopTimer);
    connect(game, &Game::flagAdded, mineCounter, &MineCounter::displayRemainingMines);
    connect(game, &Game::flagRemoved, mineCounter, &MineCounter::displayRemainingMines);

    /*
    timer->setAutoFillBackground(true);
    timer->setPalette(QPalette(QPalette::Background, Qt::red));

    mineCounter->setAutoFillBackground(true);
    mineCounter->setPalette(QPalette(QPalette::Background, Qt::blue));
    */

    mineCounter->displayRemainingMines(game->minesPlaced());

    game->mStatusBar = mStatusBar;

    game->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    layoutV2->addStretch(1);
    layoutV2->addWidget(timer);
    layoutV2->addStretch(1);
    layoutV2->addWidget(mineCounter);
    layoutV2->addStretch(1);

    //layoutH->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
    layoutH->addStretch(1);
    //layoutH->addWidget(game, 0, Qt::AlignCenter);
    layoutH->addWidget(game);
    layoutH->addLayout(layoutV2);
    layoutH->addStretch(1);
    //layoutH->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

    //layoutV1->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
    layoutV1->addStretch(1);
    layoutV1->addLayout(layoutH);
    layoutV1->addStretch(1);
    //layoutV1->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

    // Layout anwenden -> bereits bei initialisierung geschehen
    //this->setLayout(layoutV1);


}

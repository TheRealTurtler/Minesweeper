#include "interface.h"

Interface::Interface(QWidget *parent, QStatusBar* statusBar) : QWidget(parent), mStatusBar(statusBar)
{
    auto layoutH = new QHBoxLayout(this);
    //auto layoutV1 = new QVBoxLayout(this);
    auto layoutV = new QVBoxLayout;

    // Spiel erstellen
    unsigned int columns = 16;
    unsigned int rows = 16;
    unsigned int mines = 40;

    auto game = new Game(columns, rows, mines);

    //auto game = new Game(9, 9, 10, this);           // Einfach 9x9 mit 10 Mienen
    //auto game = new Game(16, 16, 40, this);           // Fortgeschritten 16x16 mit 40 Mienen
    //auto game = new Game(30, 16, 99, this);         // Experte 30x16 mit 99 Mienen

    auto aspectRatio = new AspectRatioWidget(game, columns, rows, this);

    auto timer = new Timer(this);

    auto mineCounter = new MineCounter(this);

    auto icon = new Icon(this);

    connect(game, &Game::gameStarted, timer, &Timer::startTimer);
    connect(game, &Game::gameFinished, timer, &Timer::stopTimer);
    connect(game, &Game::flagAdded, mineCounter, &MineCounter::displayRemainingMines);
    connect(game, &Game::flagRemoved, mineCounter, &MineCounter::displayRemainingMines);

    /*
    aspectRatio->setAutoFillBackground(true);
    aspectRatio->setPalette(QPalette(QPalette::Background, Qt::red));

    game->setAutoFillBackground(true);
    game->setPalette(QPalette(QPalette::Background, Qt::green));

    timer->setAutoFillBackground(true);
    timer->setPalette(QPalette(QPalette::Background, Qt::yellow));

    mineCounter->setAutoFillBackground(true);
    mineCounter->setPalette(QPalette(QPalette::Background, Qt::blue));
    */

    mineCounter->displayRemainingMines(game->minesPlaced());

    game->mStatusBar = mStatusBar;

    //game->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layoutV->addStretch(1);
    layoutV->addWidget(timer);
    layoutV->addWidget(mineCounter);
    layoutV->addStretch(1);
    layoutV->addWidget(icon);
    layoutV->addStretch(1);

    //layoutH->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
    //layoutH->addStretch(1);
    //layoutH->addWidget(game, 0, Qt::AlignCenter);
    layoutH->addWidget(aspectRatio, 1);
    layoutH->addLayout(layoutV);
    //layoutH->addStretch(1);
    //layoutH->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

    //layoutV1->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
    //layoutV1->addStretch(1);
    //layoutV1->addLayout(layoutH, 0);
    //layoutV1->addStretch(1);
    //layoutV1->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

    // Layout anwenden -> bereits bei initialisierung geschehen
    //this->setLayout(layoutV1);


}

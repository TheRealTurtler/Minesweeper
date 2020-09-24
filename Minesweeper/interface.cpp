#include "interface.h"

// Constructor
Interface::Interface(QWidget *parent, QStatusBar* statusBar) : QWidget(parent), mStatusBar(statusBar)
{
    auto layoutH = new QHBoxLayout(this);
    auto layoutV = new QVBoxLayout;

    // Spiel erstellen
    unsigned int columns = 9;
    unsigned int rows = 9;
    unsigned int mines = 10;

    mGame = new Game(columns, rows, mines);

    //auto game = new Game(9, 9, 10, this);           // Einfach 9x9 mit 10 Mienen
    //auto game = new Game(16, 16, 40, this);           // Fortgeschritten 16x16 mit 40 Mienen
    //auto game = new Game(30, 16, 99, this);         // Experte 30x16 mit 99 Mienen

    auto aspectRatio = new AspectRatioWidget(mGame, columns, rows, this);

    auto timer = new Timer(this);

    auto mineCounter = new MineCounter(this);

    auto icon = new Icon(this);

    connect(mGame, &Game::gameStarted, timer, &Timer::startTimer);
    connect(mGame, &Game::gameFinished, timer, &Timer::stopTimer);
    connect(mGame, &Game::flagAdded, mineCounter, &MineCounter::displayRemainingMines);
    connect(mGame, &Game::flagRemoved, mineCounter, &MineCounter::displayRemainingMines);
    connect(mGame, &Game::cheated, this, &Interface::cheatDetected);
    connect(mGame, &Game::gameFinished, this, &Interface::gameFinished);

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

    mineCounter->displayRemainingMines(mGame->minesPlaced());

    //mGame->mStatusBar = mStatusBar;

    layoutV->addStretch(1);
    layoutV->addWidget(timer);
    layoutV->addWidget(mineCounter);
    layoutV->addStretch(1);
    layoutV->addWidget(icon);
    layoutV->addStretch(1);

    layoutH->addWidget(aspectRatio, 1);
    layoutH->addLayout(layoutV);
}

// Cheat verwendet
void Interface::cheatDetected()
{
    mStatusBar->showMessage("Die Verwendung von Tipps führt zu einer Disqualifizierung von der Highscore Liste", 5000);

    mHighscoreQualified = false;
}

// Spiel beendet
void Interface::gameFinished(bool win)
{
    if(win)
    {
        mStatusBar->showMessage("Herzlichen Glückwunsch! Sie haben alle Mienen gefunden!", 5000);
    }
    else
    {
        mStatusBar->showMessage("Viel Glück beim nächsten Mal!", 5000);
    }
}

// Pointer auf Game Widget zurückgeben
Game *Interface::game() const
{
    return mGame;
}

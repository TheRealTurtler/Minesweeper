#include "interface.h"

// Constructor
Interface::Interface(QWidget *parent) : QWidget(parent)
{
    auto layoutH = new QHBoxLayout(this);
    auto layoutV = new QVBoxLayout;

    // Spiel erstellen
    mGame = new Game(9, 9, 10, this);           // Einfach 9x9 mit 10 Mienen
    //mGame = new Game(16, 16, 40, this);           // Fortgeschritten 16x16 mit 40 Mienen
    //mGame = new Game(30, 16, 99, this);         // Experte 30x16 mit 99 Mienen

    mAspectRatio = new AspectRatioWidget(mGame, mGame->columns(), mGame->rows(), this);

    mTimer = new Timer(this);

    mMineCounter = new MineCounter(this);

    auto icon = new Icon(this);

    connect(mGame, &Game::gameStarted, mTimer, &Timer::startTimer);
    connect(mGame, &Game::gameFinished, mTimer, &Timer::stopTimer);
    connect(mGame, &Game::flagAdded, mMineCounter, &MineCounter::displayRemainingMines);
    connect(mGame, &Game::flagRemoved, mMineCounter, &MineCounter::displayRemainingMines);
    connect(mGame, &Game::cheated, this, &Interface::cheatDetected);
    connect(mGame, &Game::gameFinished, this, &Interface::gameFinished);

    /*
    mAspectRatio->setAutoFillBackground(true);
    mAspectRatio->setPalette(QPalette(QPalette::Background, Qt::red));

    mGame->setAutoFillBackground(true);
    mGame->setPalette(QPalette(QPalette::Background, Qt::green));

    timer->setAutoFillBackground(true);
    timer->setPalette(QPalette(QPalette::Background, Qt::yellow));

    mineCounter->setAutoFillBackground(true);
    mineCounter->setPalette(QPalette(QPalette::Background, Qt::blue));
    */

    mMineCounter->displayRemainingMines(mGame->minesPlaced());

    //mGame->mStatusBar = mStatusBar;

    layoutV->addStretch(1);
    layoutV->addWidget(mTimer);
    layoutV->addWidget(mMineCounter);
    layoutV->addStretch(1);
    layoutV->addWidget(icon);
    layoutV->addStretch(1);

    layoutH->addWidget(mAspectRatio, 1);
    layoutH->addLayout(layoutV);
}

void Interface::newGame(const unsigned int columns, const unsigned int rows, const unsigned int mines)
{
    mHighscoreQualified = true;

    // Timer zurücksetzen
    mTimer->resetTimer();

    // Verbleibende Mienenanzahl zurücksetzen
    mMineCounter->displayRemainingMines(mines);

    // Spiel starten
    mGame->startGame(columns, rows, mines);

    mAspectRatio->setAspectRatio(columns, rows);
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

// StatusBar setzen
void Interface::setStatusBar(QStatusBar *statusBar)
{
    mStatusBar = statusBar;
}

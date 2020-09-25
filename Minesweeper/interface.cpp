#include "interface.h"

// Constructor
Interface::Interface(QWidget *parent) : QWidget(parent)
{
    // Layouts erstellen
    auto layoutH = new QHBoxLayout(this);
    auto layoutV = new QVBoxLayout;

    // Spiel erstellen
    mGame = new Game(9, 9, 10, this);           // Einfach 9x9 mit 10 Mienen
    //mGame = new Game(16, 16, 40, this);           // Fortgeschritten 16x16 mit 40 Mienen
    //mGame = new Game(30, 16, 99, this);         // Experte 30x16 mit 99 Mienen

    // AspectRatioWidget erstellen und Spielfeld als child übergeben
    mAspectRatio = new AspectRatioWidget(mGame, mGame->columns(), mGame->rows(), this);

    // Timer erstellen
    mTimer = new Timer(this);

    // Mienenzähler erstellen
    mMineCounter = new MineCounter(this);

    // Icon erstellen
    auto icon = new Icon(this);

    // Signale und Slots verbinden
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

    // Verbleibende Mienenzahl anzeigen
    mMineCounter->displayRemainingMines(mGame->minesPlaced());

    //mGame->mStatusBar = mStatusBar;

    // Timer und Mienenzähler zu vertikalem Layout hinzufügen
    layoutV->addStretch(1);
    layoutV->addWidget(mTimer);
    layoutV->addWidget(mMineCounter);
    layoutV->addStretch(1);
    layoutV->addWidget(icon);
    layoutV->addStretch(1);

    // AspectRatioWidget und vertikales Layout zu horizontalem Layout hinzufügen
    layoutH->addWidget(mAspectRatio, 1);
    layoutH->addLayout(layoutV);
}

// Neues Spiel mit angegebener Größe und Mienenanzahl starten
void Interface::newGame(const unsigned int columns, const unsigned int rows, const unsigned int mines)
{
    // Highscorequalifizierung zurücksetzen
    mHighscoreQualified = true;

    // Timer zurücksetzen
    mTimer->resetTimer();

    // Verbleibende Mienenanzahl zurücksetzen
    mMineCounter->displayRemainingMines(mines);

    // Spiel starten
    mGame->startGame(columns, rows, mines);

    // Seitenverhältnis aktualisieren
    mAspectRatio->setAspectRatio(columns, rows);
}

// Cheat verwendet
void Interface::cheatDetected()
{
    // Statusnachricht ausgeben
    mStatusBar->showMessage("Die Verwendung von Tipps führt zu einer Disqualifizierung von der Highscore Liste", 5000);

    // Highscore disqualifizieren
    mHighscoreQualified = false;
}

// Spiel beendet
void Interface::gameFinished(bool win)
{
    if(win)
    {
        // Statusnachricht ausgeben (gewonnen)
        mStatusBar->showMessage("Herzlichen Glückwunsch! Sie haben alle Mienen gefunden!", 5000);
    }
    else
    {
        // Statusnachricht ausgeben (verloren)
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

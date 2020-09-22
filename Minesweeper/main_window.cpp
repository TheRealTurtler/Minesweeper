#include "main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Spiel erstellen
    mGame = new Game(9, 9, 10, this);           // Einfach 9x9 mit 10 Mienen
    //mGame = new Game(16, 16, 40, this);       // Fortgeschritten 16x16 mit 40 Mienen
    //mGame = new Game(30, 16, 99, this);       // Experte 30x16 mit 99 Mienen

    // Spiel zentrieren
    setCentralWidget(mGame);
}

MainWindow::~MainWindow()
{
    // delete mGame;
}


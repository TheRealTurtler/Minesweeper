#include "main_window.h"

// Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Menüleiste erstellen
    createActions();
    createMenus();

    // Interface erstellen (beinhaltet Spielfeld, Timer, Mienenzähler)
    mInterface = new Interface(this);
    mInterface->setStatusBar(statusBar());

    // Spielfeldgrößenauswahl erstellen
    mNewGameSelection = new NewGameSelection(this);

    // Signale und Slots verbinden
    connect(mNewGameSelection, &QDialog::finished, this, &MainWindow::newGameDialogFinished);

    // Spiel zentrieren
    setCentralWidget(mInterface);
}

// Menüeinträge erstellen
void MainWindow::createActions()
{
    // Menüeintrag "Neues Spiel" von Menü "Datei"
    mNewGameAct = new QAction("Neues Spiel", this);
    mNewGameAct->setStatusTip("Neues Spiel starten");
    connect(mNewGameAct, &QAction::triggered, this, &MainWindow::newGame);

    // Menüeintrag "Beenden" von Menü "Datei"
    mExitAct = new QAction("Beenden", this);
    mExitAct->setStatusTip("Minesweeper beenden");
    connect(mExitAct, &QAction::triggered, this, &MainWindow::exit);

    // Menüeintrag "Feld untersuchen" von Menü "Tipp"
    mSearchFieldAct = new QAction("Feld untersuchen", this);
    mSearchFieldAct->setStatusTip("Wähle ein Feld aus, das auf Mienen untersucht werden soll");
    connect(mSearchFieldAct, &QAction::triggered, this, &MainWindow::searchField);

    // Menüeintrag "Spielanleitung" von Menü "Hilfe"
    mHowToPlayAct = new QAction("Spielanleitung", this);
    mHowToPlayAct->setStatusTip("Zeige die Spielanleitung von Minesweeper");
    connect(mHowToPlayAct, &QAction::triggered, this, &MainWindow::howToPlay);

    // Menüeintrag "Über" von Menü "Hilfe"
    mAboutAct = new QAction("Über", this);
    mAboutAct->setStatusTip("Informationen über Minesweeper");
    connect(mAboutAct, &QAction::triggered, this, &MainWindow::about);
}

// Menüs erstellen
void MainWindow::createMenus()
{
    // Menü Datei
    mFileMenu = menuBar()->addMenu("Datei");
    mFileMenu->addAction(mNewGameAct);
    mFileMenu->addSeparator();
    mFileMenu->addAction(mExitAct);

    // Menü Tipp
    mTipMenu = menuBar()->addMenu("Tipp");
    mTipMenu->addAction(mSearchFieldAct);

    // Menü Hilfe
    mHelpMenu = menuBar()->addMenu("Hilfe");
    mHelpMenu->addAction(mHowToPlayAct);
    mHelpMenu->addSeparator();
    mHelpMenu->addAction(mAboutAct);
}

// SLOT | Neues Spiel starten
void MainWindow::newGame()
{
    // Fenster anzeigen (open ist besser als exec) [modal, aber async]
    mNewGameSelection->open();
}

// SLOT | Auswahl der Spielfeldgröße beendet
void MainWindow::newGameDialogFinished()
{
    // Starte neues Spiel, wenn eine Auswahl getroffen wurde
    if(mNewGameSelection->result() == QDialog::Accepted)
    {
        mInterface->newGame(mNewGameSelection->columns(), mNewGameSelection->rows(), mNewGameSelection->mines());
    }
}

// SLOT | Programm beenden
void MainWindow::exit()
{
    QApplication::quit();
}

// SLOT | nächstes angeklicktes Feld auf Mienen untersuchen
void MainWindow::searchField()
{
    mInterface->game()->setMetaldetector(true);
}

// SLOT | Spielanleitung
void MainWindow::howToPlay()
{
    // Infofenster erstellen
    QMessageBox* howToPlay = new QMessageBox(this);

    // Setze flag, dass das Fenster nach dem schließen deleted wird
    howToPlay->setAttribute(Qt::WA_DeleteOnClose);

    // Überschrift
    howToPlay->setText("Spielanleitung");

    // Spielanleitung
    const QString text = QString("Linke Maustaste:\n")
            + QString("- Mienen aufdecken\n")
            + QString("- Markierungen löschen\n\n")
            + QString("Rechte Maustaste:\n")
            + QString("- 1x Fahne setzen\n")
            + QString("- 2x ?-Markierung setzen\n")
            + QString("- 3x Markierung löschen\n\n")
            + QString("Spielende:\n")
            + QString("- gewonnen: alle Felder ohne Mienen wurden aufgedeckt\n")
            + QString("- verloren: eine Miene wurde angeklickt\n\n")
            + QString("Zahlen auf aufgedeckten Feldern geben die Anzahl\n")
            + QString("benachbarter Mienen an (max 8).");

    howToPlay->setInformativeText(text);

    // Icon
    howToPlay->setIconPixmap(QPixmap(":/resources/mine.png"));

    // Fenster anzeigen (open ist besser als exec) [modal, aber async]
    howToPlay->open();
}

// SLOT | Über dieses Programm
void MainWindow::about()
{
    // Infofenster erstellen
    QMessageBox* about = new QMessageBox(this);

    // Setze flag, dass das Fenster nach dem schließen deleted wird
    about->setAttribute(Qt::WA_DeleteOnClose);

    // Überschrift
    about->setText("Minesweeper");

    // Infotext
    about->setInformativeText("Created by: Michael Diedler\n2020");

    // Icon
    about->setIconPixmap(QPixmap(":/resources/mine.png"));

    // Fenster anzeigen (open ist besser als exec) [modal, aber async]
    about->open();
}

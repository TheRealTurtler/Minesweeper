#include "new_game_selection.h"

// Constructor
NewGameSelection::NewGameSelection(QWidget* parent) : QDialog(parent)
{
    // Hilfe-Fragezeichen in der Fensterleiste ausschalten
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);

    // Layout initialisieren
    auto layout = new QGridLayout(this);

    // Buttons initialisieren
    auto buttonEasy = new QPushButton("Einfach: 9x9", this);
    auto buttonAdvanced = new QPushButton("Fortgeschritten: 16x16", this);
    auto buttonExpert = new QPushButton("Experte: 30x16", this);
    auto buttonCustom = new QPushButton("Benutzerdefiniert: #x#", this);

    // Minimale größe festlegen, es wird ansonsten eine Warnung ausgegeben
    setMinimumSize(200, 200);

    // Buttons zu Layout hinzufügen
    layout->addWidget(buttonEasy, 0, 0);
    layout->addWidget(buttonAdvanced, 0, 1);
    layout->addWidget(buttonExpert, 1, 0);
    layout->addWidget(buttonCustom, 1, 1);

    // Signale und Slots verbinden
    connect(buttonEasy, &QPushButton::clicked, this, &NewGameSelection::selectEasy);
    connect(buttonAdvanced, &QPushButton::clicked, this, &NewGameSelection::selectAdvanced);
    connect(buttonExpert, &QPushButton::clicked, this, &NewGameSelection::selectExpert);
    connect(buttonCustom, &QPushButton::clicked, this, &NewGameSelection::selectCustom);

    // Button für benutzerdefinierte Größe deaktivieren -> TODO
    buttonCustom->setEnabled(false);
}

// Spaltenanzahl zurückgeben
unsigned int NewGameSelection::columns() const
{
    return mColumns;
}

// Zeilenanzahl zurückgeben
unsigned int NewGameSelection::rows() const
{
    return mRows;
}

// Mienenanzahl zurückgeben
unsigned int NewGameSelection::mines() const
{
    return mMines;
}

// SLOT | Schwierigkeit: Einfach gewählt
void NewGameSelection::selectEasy()
{
    mColumns = 9;
    mRows = 9;
    mMines = 10;

    accept();
}

// SLOT | Schwierigkeit: Fortgeschritten gewählt
void NewGameSelection::selectAdvanced()
{
    mColumns = 16;
    mRows = 16;
    mMines = 40;

    accept();
}

// SLOT | Schwierigkeit: Experte gewählt
void NewGameSelection::selectExpert()
{
    mColumns = 30;
    mRows = 16;
    mMines = 99;

    accept();
}

// SLOT | Schwierigkeit: Benutzerdefiniert gewählt
void NewGameSelection::selectCustom()
{

}

#include "new_game_selection.h"

// Constructor
NewGameSelection::NewGameSelection(QWidget* parent) : QDialog(parent)
{
    // Hilfe-Fragezeichen in der Fensterleiste ausschalten
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);

    // Neues Widget erstellen, welches die Auswahloptionen beinhaltet
    auto selection = new QWidget();

    // Layouts initialisieren
    auto layoutSelection = new QGridLayout(selection);
    auto layout = new QVBoxLayout(this);

    // Rand des Layouts entfernen, welches die Auswahloptionen beinhaltet
    layoutSelection->setContentsMargins(0,0,0,0);

    // Größe des vectors mSelectionGrid anpassen
    mSelectionGrid.resize(4);
    mSelectionGrid.shrink_to_fit();

    // Auswahloptionen erstellen
    for(unsigned int i = 0; i < 4 ; ++i)
    {
        // Neue Größenauswahl erstellen
        auto sizeSelection = new SizeSelection(static_cast<SizeSelection::GameSize>(i), selection);

        // Minimale Größe der Auswahltaste festlegen
        sizeSelection->setMinimumSize(64,64);

        // Größenauswahl zu Layout hinzufügen
        layoutSelection->addWidget(sizeSelection, i / 2, i % 2);

        // Signal und Slot verbinden
        connect(sizeSelection, &ClickableLabel::clicked, this, &NewGameSelection::selectSize);

        // Größenauswahl in Vector speichern
        mSelectionGrid.at(i) = sizeSelection;
    }

    // Minimale größe festlegen, es wird ansonsten eine Warnung ausgegeben
    setMinimumSize(200, 200);

    // Neues AspectRatioWidget mit den Auswahloptionen als child erstellen
    auto aspectRatio = new AspectRatioWidget(selection, 2, 2, this);

    // AspectRatio zu Layout hinzufügen
    layout->addWidget(aspectRatio);
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

// Schwierigkeit: Einfach gewählt
void NewGameSelection::selectEasy()
{
    mColumns = 9;
    mRows = 9;
    mMines = 10;

    accept();
}

// Schwierigkeit: Fortgeschritten gewählt
void NewGameSelection::selectAdvanced()
{
    mColumns = 16;
    mRows = 16;
    mMines = 40;

    accept();
}

// Schwierigkeit: Experte gewählt
void NewGameSelection::selectExpert()
{
    mColumns = 30;
    mRows = 16;
    mMines = 99;

    accept();
}

// Schwierigkeit: Benutzerdefiniert gewählt
void NewGameSelection::selectCustom()
{
    // TODO
}

// SLOT | Schwierigkeit gewählt
void NewGameSelection::selectSize()
{
    SizeSelection* selection = qobject_cast<SizeSelection*>(sender());

    switch(selection->gameSize())
    {
    case SizeSelection::EASY:
        selectEasy();
        break;
    case SizeSelection::ADVANCED:
        selectAdvanced();
        break;
    case SizeSelection::EXPERT:
        selectExpert();
        break;
    case SizeSelection::CUSTOM:
        selectCustom();
        break;
    default:
        break;
    }
}

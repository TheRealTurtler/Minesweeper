#include "new_game_selection.h"

// Constructor
NewGameSelection::NewGameSelection(QWidget* parent) : QDialog(parent)
{
    // Hilfe-Fragezeichen in der Fensterleiste ausschalten
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);

    auto selection = new QWidget();

    // Layout initialisieren
    auto layoutSelection = new QGridLayout(selection);
    auto layout = new QVBoxLayout(this);

    // Rand des LAyouts entfernen
    layoutSelection->setContentsMargins(0,0,0,0);

    // Buttons initialisieren
    /*
    auto easy = new QPushButton("Einfach: 9x9", this);
    auto advanced = new QPushButton("Fortgeschritten: 16x16", this);
    auto expert = new QPushButton("Experte: 30x16", this);
    auto custom = new QPushButton("Benutzerdefiniert: #x#", this);
    */

    mSelectionGrid.resize(4);
    mSelectionGrid.shrink_to_fit();

    for(unsigned int i = 0; i < 4 ; ++i)
    {
        auto sizeSelection = new SizeSelection(static_cast<SizeSelection::GameSize>(i), selection);

        //sizeSelection->setMinimumSize(64, 64);

        // Button zu Layout hinzufügen
        layoutSelection->addWidget(sizeSelection, i / 2, i % 2);

        // Signal und Slot verbinden
        connect(sizeSelection, &ClickableLabel::clicked, this, &NewGameSelection::selectSize);

        mSelectionGrid.at(i) = sizeSelection;
    }

    //mEasy->setImage(QPixmap(":resources/easy.png"));
    //mAdvanced->setImage(QPixmap(":resources/advanced.png"));
    //mExpert->setImage(QPixmap(":resources/expert.png"));
    //mCustom->setImage(QPixmap(":resources/custom.png"));

    //mEasy->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //mAdvanced->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Minimale größe festlegen, es wird ansonsten eine Warnung ausgegeben
    setMinimumSize(200, 200);

    auto aspectRatio = new AspectRatioWidget(selection, 2, 2, this);

    layout->addWidget(aspectRatio);

    /*
    aspectRatio->setAutoFillBackground(true);
    aspectRatio->setPalette(QPalette(QPalette::Background, Qt::red));

    selection->setAutoFillBackground(true);
    selection->setPalette(QPalette(QPalette::Background, Qt::green));
    */
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



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

    layoutSelection->setContentsMargins(0,0,0,0);

    // Buttons initialisieren
    /*
    auto easy = new QPushButton("Einfach: 9x9", this);
    auto advanced = new QPushButton("Fortgeschritten: 16x16", this);
    auto expert = new QPushButton("Experte: 30x16", this);
    auto custom = new QPushButton("Benutzerdefiniert: #x#", this);
    */



    mEasy = new ClickableLabel(selection);
    mAdvanced = new ClickableLabel(selection);
    mExpert = new ClickableLabel(selection);
    mCustom = new ClickableLabel(selection);

    mEasy->setMinimumSize(64, 64);
    mAdvanced->setMinimumSize(64, 64);
    mExpert->setMinimumSize(64, 64);
    mCustom->setMinimumSize(64, 64);

    mEasy->setImage(QPixmap(":resources/easy.png"));
    mAdvanced->setImage(QPixmap(":resources/advanced.png"));
    mExpert->setImage(QPixmap(":resources/expert.png"));
    mCustom->setImage(QPixmap(":resources/custom.png"));

    //mEasy->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //mAdvanced->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Minimale größe festlegen, es wird ansonsten eine Warnung ausgegeben
    setMinimumSize(200, 200);

    // Buttons zu Layout hinzufügen
    layoutSelection->addWidget(mEasy, 0, 0);
    layoutSelection->addWidget(mAdvanced, 0, 1);
    layoutSelection->addWidget(mExpert, 1, 0);
    layoutSelection->addWidget(mCustom, 1, 1);

    // Signale und Slots verbinden
    connect(mEasy, &ClickableLabel::clicked, this, &NewGameSelection::selectEasy);
    connect(mAdvanced, &ClickableLabel::clicked, this, &NewGameSelection::selectAdvanced);
    connect(mExpert, &ClickableLabel::clicked, this, &NewGameSelection::selectExpert);
    connect(mCustom, &ClickableLabel::clicked, this, &NewGameSelection::selectCustom);

    // Button für benutzerdefinierte Größe deaktivieren -> TODO
    //custom->setEnabled(false);

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



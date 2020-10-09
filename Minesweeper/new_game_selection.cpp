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
        SizeSelection* sizeSelection;

        switch(i)
        {
        case 0:
            sizeSelection = new SizeSelection(SizeSelection::EASY, selection);
            break;
        case 1:
            sizeSelection = new SizeSelection(SizeSelection::ADVANCED, selection);
            break;
        case 2:
            sizeSelection = new SizeSelection(SizeSelection::EXPERT, selection);
            break;
        case 3:
            sizeSelection = new SizeSelection(SizeSelection::CUSTOM, selection);
            break;
        default:
            sizeSelection = nullptr;
            break;
        }

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

    // Resize-Timer initialisieren
    initResizeTimer();
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
    // CustomGameSize Fenster erstellen
    mCustomGameSize = new CustomGameSize(this);

    // Signal und Slot verbinden
    connect(mCustomGameSize, &CustomGameSize::finished, this, &NewGameSelection::selectCustomFinished);

    // Fenster anzeigen
    mCustomGameSize->open();
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

// SLOT | Benutzerdefinierte Spielfeldgröße gesetzt
void NewGameSelection::selectCustomFinished()
{
    // Überprüfung, ob eine Auswahl bestätigt wurde
    if(mCustomGameSize->result() == QDialog::Accepted)
    {
        mColumns = mCustomGameSize->columns();
        mRows = mCustomGameSize->rows();
        mMines = mCustomGameSize->mines();

        // Speicher des Auswahlfensters wieder freigeben
        delete mCustomGameSize;

        accept();
    }
    else
    {
        // Speicher des Auswahlfensters wieder freigeben
        delete mCustomGameSize;
    }
}

// Berechnung und Änderung der Schriftgröße
void NewGameSelection::resizeFont()
{
    //QLabel* biggestLabel = mSelectionGrid.at(0)->biggestLabel();

    // Aktuelle Texteigenschaften auslesen
    QFont labelFont = mSelectionGrid.at(0)->labelFont();
    const QRect baseTextRect = mSelectionGrid.at(0)->contentsRect();
    const QFontMetrics labelFontMetrics(labelFont);
    QString labelText = mSelectionGrid.at(0)->bigLabelText();

    // Längsten Text ermitteln
    for (decltype (mSelectionGrid.size()) i = 1; i < mSelectionGrid.size(); ++i)
    {
        const QString labelText2 = mSelectionGrid.at(i)->bigLabelText();

        if (labelFontMetrics.boundingRect(labelText2).width() > labelFontMetrics.boundingRect(labelText).width())
        {
            labelText = mSelectionGrid.at(i)->bigLabelText();
        }
    }

    // qMax gibt Maximum an
    // pixelSize = -1, wenn Schriftgröße mit setPointSize() festgelegt wurde
    // Schriftgrößen kleiner als 12 werden unlesbar
    unsigned int fontSize = qMax(12, labelFont.pixelSize());

    // Schrift vergrößern
    while(true)
    {
        QFont testFont(labelFont);

        testFont.setPixelSize(fontSize);

        const QRect testTextBoundingRect = QFontMetrics(testFont).boundingRect(labelText);

        // Nur Breite wichtig, da Text sowieso breiter als hoch
        if(testTextBoundingRect.width() > baseTextRect.width())
        {
            // Break, wenn Schrift breiter als die Textbox
            break;
        }

        ++fontSize;
    }

    // Schrift verkleinern
    while(fontSize > 12)
    {
        QFont testFont(labelFont);

        testFont.setPixelSize(fontSize);

        const QRect testTextBoundingRect = QFontMetrics(testFont).boundingRect(labelText);

        // Nur Breite wichtig, da Text sowieso breiter als hoch
        if(testTextBoundingRect.width() <= baseTextRect.width())
        {
            // Break, wenn Schrift wieder kleiner oder gleich Textbox
            break;
        }

        --fontSize;
    }

    // Neue Schriftgröße festlegen
    labelFont.setPixelSize(fontSize);

    // Schrift auf alle Labels anwenden
    for (decltype (mSelectionGrid.size()) i = 0; i < mSelectionGrid.size(); ++i)
    {
        mSelectionGrid.at(i)->setLabelFont(labelFont);
    }
}

// EVENT | Größe geändert
void NewGameSelection::resizeEvent(QResizeEvent *event)
{
    // Resize-Timer neustarten
    mResizeTimer->start();

    // Event weitergeben
    QDialog::resizeEvent(event);
}

// Timer initialisieren
void NewGameSelection::initResizeTimer()
{
    // Neuen single-shot Timer erstellen mit 100ms timeout
    mResizeTimer = new QTimer(this);
    mResizeTimer->setInterval(100);
    mResizeTimer->setSingleShot(true);

    // Timeout-Signal mit Schriftgrößenänderung verbinden
    connect(mResizeTimer, &QTimer::timeout, this, &NewGameSelection::resizeFont);
}

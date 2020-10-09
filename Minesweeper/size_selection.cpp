#include "size_selection.h"

SizeSelection::SizeSelection(GameSize gameSize, QWidget *parent) : ClickableLabel(parent), mGameSize(gameSize)
{
    // LAyout erstellen
    auto layout = new QVBoxLayout(this);

    // Labels erstellen
    mLabelSizeName = new QLabel(this);
    mLabelSizeNumbers = new QLabel(this);

    // Labelausrichtung festlegen
    mLabelSizeName->setAlignment(Qt::AlignCenter);
    mLabelSizeNumbers->setAlignment(Qt::AlignCenter);

    // Formatierung des LAbeltextes festlegen
    mLabelSizeName->setTextFormat(Qt::RichText);
    mLabelSizeNumbers->setTextFormat(Qt::RichText);

    // Textfarbe auf weiß festlegen
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::white);

    // Labeltextfarbe festlegen
    mLabelSizeName->setPalette(palette);
    mLabelSizeNumbers->setPalette(palette);

    // Pixmap und zugehörigen Painter erstellen
    QPixmap pixmap(64,64);
    QPainter painter(&pixmap);


    //mLabelSizeName->setAutoFillBackground(true);
    //mLabelSizeName->setPalette(QPalette(QPalette::Background, Qt::red));

    //mLabelSizeNumbers->setAutoFillBackground(true);
    //mLabelSizeNumbers->setPalette(QPalette(QPalette::Background, Qt::green));


    // Auswahloption erstellen
    switch(mGameSize)
    {
    case EASY:
        painter.fillRect(0,0,64,64,QBrush(QColor(0,138,255)));
        setImage(pixmap);
        mLabelSizeName->setText("<b>Einfach</b>");
        mLabelSizeNumbers->setText("<b>9 x 9</b>");
        break;
    case ADVANCED:
        painter.fillRect(0,0,64,64,QBrush(QColor(117,206,0)));
        setImage(pixmap);
        mLabelSizeName->setText("<b>Mittel</b>");
        mLabelSizeNumbers->setText("<b>16 x 16</b>");
        break;
    case EXPERT:
        painter.fillRect(0,0,64,64,QBrush(QColor(239,154,7)));
        setImage(pixmap);
        mLabelSizeName->setText("<b>Schwer</b>");
        mLabelSizeNumbers->setText("<b>30 x 16</b>");
        break;
    case CUSTOM:
        painter.fillRect(0,0,64,64,QBrush(QColor(239,0,11)));
        setImage(pixmap);
        mLabelSizeName->setText("<b>Benutzer</b>");
        mLabelSizeNumbers->setText("<b>? x ?</b>");
        break;
    default:
        break;
    }

    // Labels zu Layout hinzufügen
    //layout->addStretch(0);
    layout->addWidget(mLabelSizeName);
    layout->addWidget(mLabelSizeNumbers);
    //layout->addStretch(0);
}

// Gewählte Spielfeldgröße zurückgeben
SizeSelection::GameSize SizeSelection::gameSize() const
{
    return mGameSize;
}

// Auswahl Spielfeldgröße auswählen
void SizeSelection::setGameSize(const SizeSelection::GameSize gameSize)
{
    mGameSize = gameSize;
}

// Gibt die Schrift des Namens-Labels zurück (Name und Größe haben gleiche Formatierung)
QFont SizeSelection::labelFont() const
{
    return mLabelSizeName->font();
}

// Schriftgröße setzen
void SizeSelection::setLabelFont(const QFont font)
{
    mLabelSizeName->setFont(font);
    mLabelSizeNumbers->setFont(font);
}

// Gibt den Text des größten Labels (also den längsten Text) zurück
QString SizeSelection::bigLabelText() const
{
    return biggestLabel()->text();
}

QRect SizeSelection::bigLabelContentsRect() const
{
    return biggestLabel()->contentsRect();
}

// PRIVATE | Größtes Label ausgeben
QLabel *SizeSelection::biggestLabel() const
{
    // Bestimmen, welcher Text länger ist
    if (QFontMetrics(mLabelSizeName->font()).boundingRect(mLabelSizeName->text()).width() > QFontMetrics(mLabelSizeNumbers->font()).boundingRect(mLabelSizeNumbers->text()).width())
    {
        return mLabelSizeName;
    }
    else
    {
        return mLabelSizeNumbers;
    }
}

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

    initResizeTimer();
}

// Gewählte Spielfeldgröße zurückgeben
SizeSelection::GameSize SizeSelection::gameSize() const
{
    return mGameSize;
}

// Auswahl Spielfeldgröße auswählen
void SizeSelection::setGameSize(SizeSelection::GameSize gameSize)
{
    mGameSize = gameSize;
}

// Berechnung und Änderung der Schriftgröße
void SizeSelection::resizeFont()
{
    QLabel* biggerLabel;
    QLabel* smallerLabel;

    // Bestimmen, welcher Text länger ist
    if (QFontMetrics(mLabelSizeName->font()).boundingRect(mLabelSizeName->text()).width() > QFontMetrics(mLabelSizeNumbers->font()).boundingRect(mLabelSizeNumbers->text()).width())
    {
        biggerLabel = mLabelSizeName;
        smallerLabel = mLabelSizeNumbers;
    }
    else
    {
        biggerLabel = mLabelSizeNumbers;
        smallerLabel = mLabelSizeName;
    }

    // Aktuelle Texteigenschaften auslesen
    QFont baseFont = biggerLabel->font();
    const QRect baseTextRect = biggerLabel->contentsRect();
    const QString baseText = biggerLabel->text();

    // qMax gibt Maximum an
    // pixelSize = -1, wenn Schriftgröße mit setPointSize() festgelegt wurde
    // Schriftgrößen kleiner als 12 werden unlesbar
    unsigned int fontSize = qMax(12, baseFont.pixelSize());

    // Schrift vergrößern
    while(true)
    {
        QFont testFont(baseFont);

        testFont.setPixelSize(fontSize);

        const QRect testTextBoundingRect = QFontMetrics(testFont).boundingRect(baseText);

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
        QFont testFont(baseFont);

        testFont.setPixelSize(fontSize);

        const QRect testTextBoundingRect = QFontMetrics(testFont).boundingRect(baseText);

        // Nur Breite wichtig, da Text sowieso breiter als hoch
        if(testTextBoundingRect.width() <= baseTextRect.width())
        {
            // Break, wenn Schrift wieder kleiner oder gleich Textbox
            break;
        }

        --fontSize;
    }

    // Neue Schriftgröße festlegen
    baseFont.setPixelSize(fontSize);
    biggerLabel->setFont(baseFont);
    smallerLabel->setFont(baseFont);
}

// EVENT | Größe geändert
void SizeSelection::resizeEvent(QResizeEvent *event)
{
    // Resize-Timer neustarten
    mResizeTimer->start();

    // Event weitergeben
    ClickableLabel::resizeEvent(event);
}

// Timer initialisieren
void SizeSelection::initResizeTimer()
{
    // Neuen single-shot Timer erstellen mit 100ms timeout
    mResizeTimer = new QTimer(this);
    mResizeTimer->setInterval(10);
    mResizeTimer->setSingleShot(true);

    // Timeout-Signal mit Schriftgrößenänderung verbinden
    connect(mResizeTimer, &QTimer::timeout, this, &SizeSelection::resizeFont);
}

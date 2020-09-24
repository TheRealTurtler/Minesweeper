#include "mine_field.h"

#include <QPainter>

MineField::MineField(QWidget *parent) : QLabel(parent)
{
    setFlagState(NONE);
}

// Überprüfe, ob dieses Feld eine Miene beinhaltet
bool MineField::isMine()
{
    return mIsMine;
}

// Setze / Entferne eine Miene von diesem Feld
void MineField::setMine(bool isMine)
{
    mIsMine = isMine;
}

// Überprüfe, ob dieses Feld bereits untersucht wurde
bool MineField::cleared()
{
    return mCleared;
}

// Markiere dieses Feld als bereits untersucht
void MineField::setCleared(bool cleared)
{
    mCleared = cleared;

    switch(mMinesNearby)
    {
    case 0:
        setImage(QPixmap(":/resources/empty.png"));
        break;
    case 1:
        setImage(QPixmap(":/resources/empty.png"), QPixmap(":/resources/nearby1.png"));
        break;
    case 2:
        setImage(QPixmap(":/resources/empty.png"), QPixmap(":/resources/nearby2.png"));
        break;
    case 3:
        setImage(QPixmap(":/resources/empty.png"), QPixmap(":/resources/nearby3.png"));
        break;
    case 4:
        setImage(QPixmap(":/resources/empty.png"), QPixmap(":/resources/nearby4.png"));
        break;
    case 5:
        setImage(QPixmap(":/resources/empty.png"), QPixmap(":/resources/nearby5.png"));
        break;
    case 6:
        setImage(QPixmap(":/resources/empty.png"), QPixmap(":/resources/nearby6.png"));
        break;
    case 7:
        setImage(QPixmap(":/resources/empty.png"), QPixmap(":/resources/nearby7.png"));
        break;
    case 8:
        setImage(QPixmap(":/resources/empty.png"), QPixmap(":/resources/nearby8.png"));
        break;
    default:
        break;
    }
}

// Überprüfe, wie viele Mienenfelder dieses Feld als Nachbarfelder hat
unsigned short MineField::minesNearby()
{
    return mMinesNearby;
}

// Setze die Anzahl der benachbarten Mienenfelder
void MineField::setMinesNearby(unsigned short minesNearby)
{
    mMinesNearby = minesNearby;
}

// Bild dieses Feldes abfragen
QPixmap MineField::pixmap()
{
    return mPixmap;
}

// Bild für dieses Feld festlegen
void MineField::setImage(const QPixmap &pixmap)
{
    setPixmap(pixmap.scaled(sizeHint(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    mPixmap = pixmap;
}

void MineField::setImage(const QPixmap &basePixmap, const QPixmap &overlayPixmap)
{
    //QPixmap* pixmap = new QPixmap(basePixmap);
    QPainter* painter = new QPainter(&mPixmap);

    painter->drawPixmap(0, 0, basePixmap);
    painter->drawPixmap(0, 0, overlayPixmap);

    setPixmap(mPixmap.scaled(sizeHint(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    delete painter;
}

// Überprüfe den Flaggenstatus dieses Feldes
MineField::FlagState MineField::flagState()
{
    return mFlagState;
}

// Setze den Flaggenstatus dieses Feldes
void MineField::setFlagState(MineField::FlagState flagState)
{
    mFlagState = flagState;

    switch(mFlagState)
    {
    case NONE:
        setImage(QPixmap(":/resources/field.png"));
        break;
    case FLAGGED:
        setImage(QPixmap(":/resources/field.png"), QPixmap(":/resources/flag.png"));
        break;
    case UNKNOWN:
        setImage(QPixmap(":/resources/field.png"), QPixmap(":/resources/unknown.png"));
        break;
    default:
        break;
    }
}

// EVENT | Signal je nach Mausklick ausgeben
void MineField::mousePressEvent(QMouseEvent* event)
{
    const auto& button = event->button();

    if(button == Qt::LeftButton)
    {
        emit leftClicked();

        return;
    }

    if(button == Qt::RightButton)
    {
        emit rightClicked();

        return;
    }

    return QWidget::mousePressEvent(event);
}

// EVENT | Fenstergröße geändert -> wahrscheinlich hier unnötig
void MineField::resizeEvent(QResizeEvent *event)
{
    // Überprüfen, ob sich die Größe wirklich verändert hat
    if(event->oldSize() != size())
    {
        // Größe ändern
        setPixmap(mPixmap.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

        return;
    }

    // Event weitergeben
    return QLabel::resizeEvent(event);
}

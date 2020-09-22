#include "mine_field.h"

MineField::MineField(QWidget *parent) : QLabel(parent)
{

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
    this->setPixmap(pixmap.scaled(this->sizeHint(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    mPixmap = pixmap;
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

    QWidget::mousePressEvent(event);
}

// EVENT | Fenstergröße geändert -> wahrscheinlich hier unnötig
void MineField::resizeEvent(QResizeEvent *event)
{
    //this->setPixmap(mPixmap.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QLabel::resizeEvent(event);
}

#include "clickable_label.h"

// Constructor
ClickableLabel::ClickableLabel(QWidget* parent) : QLabel(parent)
{

}

// Bild dieses Feldes abfragen
QPixmap ClickableLabel::originalPixmap()
{
    return mPixmap;
}

// Bild für dieses Feld festlegen
void ClickableLabel::setImage(const QPixmap &pixmap)
{
    setPixmap(pixmap.scaled(sizeHint(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    mPixmap = pixmap;
}

// Bild mit transparentem Overlay für dieses Feld festlegen
void ClickableLabel::setImage(const QPixmap &basePixmap, const QPixmap &overlayPixmap)
{
    QPainter* painter = new QPainter(&mPixmap);

    painter->drawPixmap(0, 0, basePixmap);
    painter->drawPixmap(0, 0, overlayPixmap);

    setPixmap(mPixmap.scaled(sizeHint(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    delete painter;
}

// EVENT | Signal je nach Mausklick ausgeben
void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();

        return;
    }

    return QLabel::mousePressEvent(event);
}

// EVENT | Größe geändert
void ClickableLabel::resizeEvent(QResizeEvent *event)
{
    // Überprüfen, ob sich die Größe wirklich verändert hat
    if(event->oldSize() != size())
    {
        // Größe ändern
        setPixmap(originalPixmap().scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

        return;
    }

    // Event weitergeben
    return QLabel::resizeEvent(event);
}

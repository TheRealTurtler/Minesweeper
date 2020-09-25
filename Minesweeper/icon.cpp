#include "icon.h"

// Constructor
Icon::Icon(QWidget *parent) : QWidget(parent)
{
    QPixmap pixmap(":/resources/mine.png");

    auto icon = new QLabel(this);
    icon->setPixmap(pixmap);

    auto text = new QLabel("Minesweeper", this);

    auto layout = new QVBoxLayout(this);

    icon->setAlignment(Qt::AlignCenter);
    text->setAlignment(Qt::AlignCenter);

    layout->addWidget(icon);
    layout->addWidget(text);
}

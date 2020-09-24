#include "icon.h"

Icon::Icon(QWidget *parent) : QWidget(parent)
{
    auto pixmap = QPixmap(":/resources/mine.png");

    auto icon = new QLabel(this);
    icon->setPixmap(pixmap);

    auto text = new QLabel("Minesweeper", this);

    auto layout = new QVBoxLayout(this);

    icon->setAlignment(Qt::AlignCenter);
    text->setAlignment(Qt::AlignCenter);

    layout->addWidget(icon);
    layout->addWidget(text);
}

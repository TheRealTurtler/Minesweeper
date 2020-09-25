#include "size_selection.h"

SizeSelection::SizeSelection(GameSize gameSize, QWidget *parent) : ClickableLabel(parent), mGameSize(gameSize)
{
    auto layout = new QVBoxLayout(this);

    auto labelSizeName = new QLabel(this);
    auto labelSizeNumbers = new QLabel(this);

    labelSizeName->setAlignment(Qt::AlignCenter);
    labelSizeNumbers->setAlignment(Qt::AlignCenter);

    labelSizeName->setTextFormat(Qt::RichText);
    labelSizeNumbers->setTextFormat(Qt::RichText);

    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::white);

    labelSizeName->setPalette(palette);
    labelSizeNumbers->setPalette(palette);

    QPixmap pixmap(64,64);
    auto painter = new QPainter(&pixmap);

    switch(mGameSize)
    {
    case EASY:
        painter->fillRect(0,0,64,64,QBrush(QColor(0,138,255)));
        setImage(pixmap);
        labelSizeName->setText("<b>Einfach</b>");
        labelSizeNumbers->setText("<b>9 x 9</b>");
        break;
    case ADVANCED:
        painter->fillRect(0,0,64,64,QBrush(QColor(117,206,0)));
        setImage(pixmap);
        labelSizeName->setText("<b>Mittel</b>");
        labelSizeNumbers->setText("<b>16 x 16</b>");
        break;
    case EXPERT:
        painter->fillRect(0,0,64,64,QBrush(QColor(239,154,7)));
        setImage(pixmap);
        labelSizeName->setText("<b>Schwer</b>");
        labelSizeNumbers->setText("<b>30 x 16</b>");
        break;
    case CUSTOM:
        painter->fillRect(0,0,64,64,QBrush(QColor(239,0,11)));
        setImage(pixmap);
        labelSizeName->setText("<b>Benutzer</b>");
        labelSizeNumbers->setText("<b>? x ?</b>");
        break;
    default:
        break;
    }

    layout->addStretch(1);
    layout->addWidget(labelSizeName);
    layout->addWidget(labelSizeNumbers);
    layout->addStretch(1);

    delete painter;
}

SizeSelection::GameSize SizeSelection::gameSize() const
{
    return mGameSize;
}

void SizeSelection::setGameSize(SizeSelection::GameSize gameSize)
{
    mGameSize = gameSize;
}

#include "aspect_ratio_widget.h"

// Diese Klasse wurde unter Zuhilfenahme von https://stackoverflow.com/a/30008442 erstellt

AspectRatioWidget::AspectRatioWidget(QWidget *widget, float aspectRatio, QWidget *parent)
    : QWidget(parent), mAspectRatio(aspectRatio)
{
    // Falls nicht schon der Fall wird dieses Widget als parent vom angegebenen Widget gesetzt
    widget->setParent(this);

    mLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);

    //mLayout->addItem(new QSpacerItem(0, 0));
    mLayout->addStretch();
    mLayout->addWidget(widget);
    mLayout->addStretch();
    //mLayout->addItem(new QSpacerItem(0, 0));
}

AspectRatioWidget::AspectRatioWidget(QWidget *widget, float width, float height, QWidget *parent)
    : AspectRatioWidget(widget, width / height, parent)
{

}

void AspectRatioWidget::stretchLayout()
{
    float currentAspectRatio = static_cast<float>(width()) / height();
    int stretchFactorWidget = 0;
    int stretchFactorSpacing = 0;

    if(currentAspectRatio > mAspectRatio)
    {
        // Widget ist zu breit

        mLayout->setDirection(QBoxLayout::LeftToRight);
        stretchFactorWidget = height() * mAspectRatio;                      // = neue Breite
        stretchFactorSpacing = (width() - stretchFactorWidget) / 2 + 1;     // + 1 für Rechenfehler von in division
    }
    else
    {
        // Widget ist zu hoch

        mLayout->setDirection(QBoxLayout::TopToBottom);
        stretchFactorWidget = width() / mAspectRatio;                       // = neue Höhe
        stretchFactorSpacing = (height() - stretchFactorWidget) / 2 + 1;    // + 1 für Rechenfehler von in division
    }

    mLayout->setStretch(0, stretchFactorSpacing);
    mLayout->setStretch(1, stretchFactorWidget);
    mLayout->setStretch(2, stretchFactorSpacing);
}

void AspectRatioWidget::setAspectRatio(float aspectRatio)
{
    mAspectRatio = aspectRatio;

    stretchLayout();
}

void AspectRatioWidget::setAspectRatio(float width, float height)
{
    setAspectRatio(width / height);
}

void AspectRatioWidget::resizeEvent(QResizeEvent *event)
{
    // Überprüfen, ob sich Größe wirklich geändert hat
    if(event->oldSize() != size())
    {
        stretchLayout();

        return;
    }

    // Event weitergeben
    return QWidget::resizeEvent(event);
}



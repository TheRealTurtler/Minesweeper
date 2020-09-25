#ifndef SIZE_SELECTION_H
#define SIZE_SELECTION_H

#include <QVBoxLayout>

#include "clickable_label.h"

class SizeSelection : public ClickableLabel
{
    Q_OBJECT
public:
    enum GameSize
    {
        EASY,
        ADVANCED,
        EXPERT,
        CUSTOM
    };

    explicit SizeSelection(GameSize gameSize, QWidget *parent = nullptr);

    // Get und Set Funktionen
    GameSize gameSize() const;
    void setGameSize(GameSize gameSize);

signals:

private:
    GameSize mGameSize;

};

#endif // SIZE_SELECTION_H

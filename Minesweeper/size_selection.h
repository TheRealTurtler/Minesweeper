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
    void setGameSize(const GameSize gameSize);
    QFont labelFont() const;
    void setLabelFont(const QFont font);
    QString bigLabelText() const;
    QRect bigLabelContentsRect() const;

signals:

private:
    GameSize mGameSize;
    QTimer* mResizeTimer = nullptr;

    QLabel* mLabelSizeName = nullptr;
    QLabel* mLabelSizeNumbers = nullptr;

    QLabel* biggestLabel() const;
};

#endif // SIZE_SELECTION_H

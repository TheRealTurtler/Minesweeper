#ifndef MINE_FIELD_H
#define MINE_FIELD_H

#include <QMouseEvent>

#include "clickable_label.h"

class MineField : public ClickableLabel
{
    Q_OBJECT

public:
    explicit MineField(QWidget* parent = nullptr);

    enum FlagState
    {
        NONE,
        FLAGGED,
        UNKNOWN,
        DETECTED
    };

    // Get und Set Funktionen
    bool isMine();
    void setMine(bool isMine);
    bool cleared();
    void setCleared(bool cleared);
    unsigned short minesNearby();
    void setMinesNearby(unsigned short minesNearby);
    FlagState flagState();
    void setFlagState(FlagState flagState);

signals:
    void leftClicked();
    void rightClicked();

protected:
   virtual void mousePressEvent(QMouseEvent* event) override;

private:
   bool mIsMine = false;
   bool mCleared = false;
   FlagState mFlagState = NONE;
   unsigned short mMinesNearby = 0;
};

#endif // MINE_FIELD_H

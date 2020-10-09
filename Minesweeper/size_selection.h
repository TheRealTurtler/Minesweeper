#ifndef SIZE_SELECTION_H
#define SIZE_SELECTION_H

#include <QVBoxLayout>
#include <QTimer>

#include "clickable_label.h"

#include <QDebug>

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

public slots:
    void resizeFont();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

signals:

private:
    GameSize mGameSize;
    QTimer* mResizeTimer = nullptr;

    QLabel* mLabelSizeName = nullptr;
    QLabel* mLabelSizeNumbers = nullptr;

    void initResizeTimer();

};

#endif // SIZE_SELECTION_H

#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QGridLayout>
#include <QBoxLayout>
#include <QStatusBar>

#include "game.h"
#include "mine_counter.h"
#include "timer.h"
#include "aspect_ratio_widget.h"
#include "icon.h"
#include "best_time.h"

class Interface : public QWidget
{
    Q_OBJECT

public:
    explicit Interface(QWidget *parent = nullptr);

    void newGame(const unsigned int columns, const unsigned int rows, const unsigned int mines);

    // Get und Set Funktionen
    Game* game() const;
    void setStatusBar(QStatusBar* statusBar);


public slots:
    void cheatDetected();
    void gameFinished(bool win);

signals:

private:
    Game* mGame;
    AspectRatioWidget* mAspectRatio;
    Timer* mTimer;
    MineCounter* mMineCounter;
    BestTime* mBestTime;

    QStatusBar* mStatusBar = nullptr;

    bool mHighscoreQualified = true;
};

#endif // INTERFACE_H

#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QGridLayout>
#include <QBoxLayout>

#include "game.h"
#include "mine_counter.h"
#include "timer.h"
#include "aspect_ratio_widget.h"
#include "icon.h"

class Interface : public QWidget
{
    Q_OBJECT
public:
    explicit Interface(QWidget *parent = nullptr, QStatusBar* statusBar = nullptr);

    // Get und Set Funktionen
    Game* game() const;

    QStatusBar* mStatusBar = nullptr;

public slots:
    void cheatDetected();
    void gameFinished(bool win);

signals:

private:
    Game* mGame;

    bool mHighscoreQualified = true;
};

#endif // INTERFACE_H

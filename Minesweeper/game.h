#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QIcon>
#include <random>
#include <algorithm>
//#include <QStatusBar>

#include "mine_field.h"

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(const unsigned int columns, const unsigned int rows, const unsigned int mines, QWidget *parent = nullptr);

    ~Game();

    void spreadMines(const unsigned int amount);
    std::vector<MineField*> getNearby(const unsigned int column, const unsigned int row) const;
    std::vector<MineField*> getNearby(const unsigned int index) const;
    std::vector<MineField*> getNearby(const MineField* mineField) const;
    void checkNearbyMines(const unsigned int column, const unsigned int row);
    void checkNearbyMines(const unsigned int index);
    void searchField(MineField* mineField);

public slots:
    void slotSearchField();
    void slotFlagMine();

signals:

protected:
   virtual void resizeEvent(QResizeEvent* event) override;

private:
    std::vector<MineField*> mMineGrid;
    std::vector<MineField*> mExplosiveFields;

    const unsigned int mColumns = 0;
    const unsigned int mRows = 0;
    const unsigned int mMines = 0;

    bool mFirstClick = true;
    bool mGameOver = false;

    QSize mMineFieldSize;

    // RNG
    std::mt19937 mRandomEngine;
    std::uniform_int_distribution<size_t> mDistribution;

    //QStatusBar* statusBar;
};

#endif // GAME_H

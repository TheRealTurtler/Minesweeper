#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGridLayout>
#include <QBoxLayout>
#include <QIcon>
#include <random>
#include <algorithm>
#include <QStatusBar>
#include <QResizeEvent>

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
    void detectMine(MineField* mineField);
    QPoint getFieldPosition(unsigned int index);

    // Get und Set Funktionen
    unsigned int minesPlaced() const;
    bool metalDetector() const;
    void setMetaldetector(bool metalDetector);

    // DEBUG
    //QStatusBar* mStatusBar = nullptr;

public slots:
    void slotSearchField();
    void slotFlagMine();

signals:
    void gameStarted();
    void gameFinished(bool win);
    void flagAdded(int remainingMines);
    void flagRemoved(int remainingMines);
    void mineDetected(bool mineDetected);
    void cheated();

protected:
   virtual void resizeEvent(QResizeEvent* event) override;

private:
    std::vector<MineField*> mMineGrid;          // Spielfeld
    std::vector<MineField*> mExplosiveFields;   // Felder mit Mienen

    const unsigned int mColumns = 0;    // Spielfeld Spalten
    const unsigned int mRows = 0;       // Spielfeld Reihen
    const unsigned int mMines = 0;      // Auf dem Spielfeld platzierte Mienen
    const unsigned int mSpace = 4;      // Abstand zwischen den Feldern

    unsigned int mFlags = 0;            // Anzahl gesetzter Flaggen

    bool mFirstClick = true;
    bool mGameOver = false;
    bool mMetalDetector = false;

    const QSize mMineFieldMinimumSize = QSize(32, 32);;      // Mindestgröße eines Mienenfeldes
    QSize mMineFieldSize = mMineFieldMinimumSize;                   // Größe eines Mienenfeldes

    // RNG
    std::mt19937 mRandomEngine;
    std::uniform_int_distribution<size_t> mDistribution;

    //QStatusBar* statusBar;
};

#endif // GAME_H

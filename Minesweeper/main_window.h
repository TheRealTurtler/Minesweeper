#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QApplication>
#include <QMessageBox>

#include "interface.h"
#include "new_game_selection.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    void createActions();
    void createMenus();

    QMenu* mFileMenu;
    QMenu* mTipMenu;
    QMenu* mHelpMenu;

    QAction* mNewGameAct;
    QAction* mExitAct;
    QAction* mSearchFieldAct;
    QAction* mHowToPlayAct;
    QAction* mAboutAct;

    Interface* mInterface;
    NewGameSelection* mNewGameSelection;

private slots:
    void newGame();
    void newGameDialogFinished();
    void exit();
    void searchField();
    void howToPlay();
    void about();
};
#endif // MAIN_WINDOW_H

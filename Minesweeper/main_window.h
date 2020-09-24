#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QApplication>
#include <QMessageBox>

#include "interface.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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

private slots:
    void newGame();
    void exit();
    void searchField();
    void howToPlay();
    void about();
};
#endif // MAINWINDOW_H

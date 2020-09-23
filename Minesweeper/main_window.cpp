#include "main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto interface = new Interface(this, statusBar());
    //auto interface = new Interface(this);

    /*
    QPalette pal;
    pal.setColor(QPalette::Background, Qt::black);

    interface->setAutoFillBackground(true);
    interface->setPalette(pal);
    */

    // Spiel zentrieren
    setCentralWidget(interface);
}

MainWindow::~MainWindow()
{
    // delete mGame;
}

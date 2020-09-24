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

    // DEBUG
    QStatusBar* mStatusBar = nullptr;

signals:

};

#endif // INTERFACE_H

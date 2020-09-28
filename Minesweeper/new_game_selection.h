#ifndef NEW_GAME_SELECTION_H
#define NEW_GAME_SELECTION_H

#include <QDialog>
#include <QGridLayout>
//#include <QPushButton>
#include <QVBoxLayout>

#include "aspect_ratio_widget.h"
#include "size_selection.h"
#include "custom_game_size.h"

class NewGameSelection : public QDialog
{
    Q_OBJECT

public:
    explicit NewGameSelection(QWidget* parent = nullptr);

    void selectEasy();
    void selectAdvanced();
    void selectExpert();
    void selectCustom();

    // Get und Set Funktionen
    unsigned int columns() const;
    unsigned int rows() const;
    unsigned int mines() const;

public slots:
    void selectSize();
    void selectCustomFinished();

signals:
    void selectedDefaultSize(int size);
    void selectedCustomSize(int* size);

private:
    unsigned int mColumns = 0;
    unsigned int mRows = 0;
    unsigned int mMines = 0;

    std::vector<SizeSelection*> mSelectionGrid;

    CustomGameSize* mCustomGameSize;
};

#endif // NEW_GAME_SELECTION_H

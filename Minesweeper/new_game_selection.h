#ifndef NEW_GAME_SELECTION_H
#define NEW_GAME_SELECTION_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>

class NewGameSelection : public QDialog
{
    Q_OBJECT

public:
    explicit NewGameSelection(QWidget* parent);

    // Get und Set Funktionen
    unsigned int columns() const;
    unsigned int rows() const;
    unsigned int mines() const;

public slots:
    void selectEasy();
    void selectAdvanced();
    void selectExpert();
    void selectCustom();

signals:
    void selectedDefaultSize(int size);
    void selectedCustomSize(int* size);

private:
    unsigned int mColumns = 0;
    unsigned int mRows = 0;
    unsigned int mMines = 0;
};

#endif // NEW_GAME_SELECTION_H

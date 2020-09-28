#ifndef CUSTOM_GAME_SIZE_H
#define CUSTOM_GAME_SIZE_H

#include <QDialog>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QMessageBox>

class CustomGameSize : public QDialog
{
    Q_OBJECT

public:
    explicit CustomGameSize(QWidget *parent = nullptr);

    // Get und Set Funktionen
    unsigned int columns();
    unsigned int rows();
    unsigned int mines();

public slots:
    void pressedOk();
    void pressedCancel();

signals:

private:
    unsigned int mColumns = 0;
    unsigned int mRows = 0;
    unsigned int mMines = 0;

    QSpinBox* mSpinboxColumns;
    QSpinBox* mSpinboxRows;
    QSpinBox* mSpinboxMines;
};

#endif // CUSTOM_GAME_SIZE_H

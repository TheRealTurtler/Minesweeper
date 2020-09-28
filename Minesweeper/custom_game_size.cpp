#include "custom_game_size.h"

CustomGameSize::CustomGameSize(QWidget *parent) : QDialog(parent)
{
    // Hilfe-Fragezeichen in der Fensterleiste ausschalten
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);

    // Layout erstellen
    auto layoutG = new QGridLayout(this);

    // Labels erstellen
    auto labelColumns = new QLabel("Spalten:", this);
    auto labelRows = new QLabel("Zeilen:", this);
    auto labelMines = new QLabel("Mienen:", this);

    // Spinboxen erstellen
    mSpinboxColumns = new QSpinBox(this);
    mSpinboxRows = new QSpinBox(this);
    mSpinboxMines = new QSpinBox(this);

    // Buttonbox erstellen
    auto buttonBox = new QDialogButtonBox(this);

    // Minimalwerte für Spinboxen festlegen
    mSpinboxColumns->setMinimum(4);
    mSpinboxRows->setMinimum(4);
    mSpinboxMines->setMinimum(1);

    // Maximalwerte für Spinboxen festlegen
    mSpinboxColumns->setMaximum(100);
    mSpinboxRows->setMaximum(50);
    mSpinboxMines->setMaximum(5000);

    // Standardwerte für Spinboxen festlegen
    mSpinboxColumns->setValue(9);
    mSpinboxRows->setValue(9);
    mSpinboxMines->setValue(10);

    // Spinboxausrichtung festlegen
    mSpinboxColumns->setAlignment(Qt::AlignRight);
    mSpinboxRows->setAlignment(Qt::AlignRight);
    mSpinboxMines->setAlignment(Qt::AlignRight);

    // Ok und Abbrechen zu Buttonbox hinzufügen
    buttonBox->addButton(QDialogButtonBox::Ok);
    buttonBox->addButton(QDialogButtonBox::Cancel);

    // Signale und Slots verbinden
    connect(buttonBox, &QDialogButtonBox::accepted, this, &CustomGameSize::pressedOk);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &CustomGameSize::pressedCancel);

    // Labels, Spinboxen und Buttonbox zu Layout hinzufügen
    layoutG->addWidget(labelColumns, 0, 0);
    layoutG->addWidget(labelRows, 1, 0);
    layoutG->addWidget(labelMines, 2, 0);
    layoutG->addWidget(mSpinboxColumns, 0, 1);
    layoutG->addWidget(mSpinboxRows, 1, 1);
    layoutG->addWidget(mSpinboxMines, 2, 1);
    layoutG->addWidget(buttonBox, 4, 1);

    // Minimale Fenstergröße festlegen (ansonsten wird eine Warnung ausgegeben)
    setMinimumSize(200, 130);
}

// Eingegebenen Wert für Spaltenanzahl zurückgeben
unsigned int CustomGameSize::columns()
{
    return mSpinboxColumns->value();
}

// Eingegebenen Wert für Zeilenanzahl zurückgeben
unsigned int CustomGameSize::rows()
{
    return mSpinboxRows->value();
}

// Eingegebenen Wert für Mienenanzahl zurückgeben
unsigned int CustomGameSize::mines()
{
    return mSpinboxMines->value();
}

// SLOT | Ok Button gedrückt
void CustomGameSize::pressedOk()
{
    // Überprüfen, ob eingegebene Werte Sinn machen
    if(mSpinboxColumns->value() * mSpinboxRows->value() - 9 >= mSpinboxMines->value())
    {
        accept();
    }
    else
    {
        // Warnung ausgeben
        QString text = QString("Angegebene Mienenanzahl ist zu groß für gewählte Spielfeldgröße!\n\n")
                + QString("Es dürfen höchstens %1 Mienen auf einem %2 * %3 Spielfeld platziert werden!")
                .arg(mSpinboxColumns->value() * mSpinboxRows->value() - 9)
                .arg(mSpinboxColumns->value())
                .arg(mSpinboxRows->value());

        QMessageBox::warning(this, "Warnung", text);
    }
}

// SLOT | Abbrechen Button gedrückt
void CustomGameSize::pressedCancel()
{
    reject();
}

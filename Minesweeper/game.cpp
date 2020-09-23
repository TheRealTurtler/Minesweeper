#include "game.h"

// Constructor
Game::Game(const unsigned int columns, const unsigned int rows, const unsigned int mines, QWidget *parent)
    : QWidget(parent), mColumns(columns), mRows(rows), mMines(mines)
{
    // TODO
    // Layout erstellen
    //QHBoxLayout* layoutH = new QHBoxLayout;
    //QVBoxLayout* layoutV = new QVBoxLayout;
    //QGridLayout* gameLayout = new QGridLayout(this);

    // TODO
    // Mienenfeldgröße initialisieren
    mMineFieldSize = QSize(48, 48);

    // Vectorgröße anpassen
    mMineGrid.resize(mRows * mColumns);
    mMineGrid.shrink_to_fit();

    // Spielfeld erstellen
    for(auto r = decltype (rows) {0}; r < mRows; ++r)
    {
        for(auto c = decltype (rows) {0}; c < mColumns; ++c)
        {
            MineField* mineField = new MineField(this);

            mineField->setMinimumSize(16, 16);
            mineField->setScaledContents(true);
            mineField->setPixmap(mineField->pixmap().scaled(mMineFieldSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            mineField->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

            //gameLayout->addWidget(mineField, r, c);

            mineField->setGeometry(c * (mMineFieldSize.width() + mSpace), r * (mMineFieldSize.height() + mSpace), mMineFieldSize.width(), mMineFieldSize.height());

            connect(mineField, &MineField::leftClicked, this, &Game::slotSearchField);
            connect(mineField, &MineField::rightClicked, this, &Game::slotFlagMine);

            mMineGrid.at(c + r * mColumns) = mineField;
        }
    }

    setMinimumSize(mColumns * mMineFieldSize.width() + (mColumns - 1) * mSpace, mRows * mMineFieldSize.height() + (mRows - 1) * mSpace);

    //auto layout = new QVBoxLayout(this);

    //layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::Ignored));

    //setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //adjustSize();




    /*  // Macht keinen Unterschied
    for(unsigned int i = 0; i < mRows; ++i)
    {
        gameLayout->setRowStretch(i, 0);
    }

    for(unsigned int i = 0; i < mColumns; ++i)
    {
        gameLayout->setColumnStretch(i, 0);
    }
    */

    // Abstand zwischen den Feldern festlegen
    //gameLayout->setSpacing(mSpace);

    // TODO
    // Spacer im Spielfeld herum hinzufügen
    //layoutH->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    //layoutH->addLayout(gameLayout);
    //layoutH->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    //layoutV->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    //layoutV->addLayout(layoutH);
    //layoutV->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    // Layout anwenden -> bereits bei initialisierung geschehen
    //this->setLayout(gameLayout);

    // RNG Initialisierung
    std::random_device randomDevice;
    mRandomEngine = std::mt19937(randomDevice());
    mDistribution = std::uniform_int_distribution<size_t>(0, mMineGrid.size() - 1);
}

// Destructor
Game::~Game()
{
    /*
    for(auto i : mMineGrid)
    {
        delete i;
    }
    */
}

// Zufällig Mienen auf dem Spielfeld verteilen
void Game::spreadMines(const unsigned int amount)
{
    // Return wenn mehr Mienen platziert werden sollen, als Felder vorhanden sind
    if(amount > mMineGrid.size())
    {
        return;
    }

    // Mienen zufällig verteilen
    for(auto i = decltype (amount) {0}; i < amount; ++i)    // auto i = ... weil amount const ist
    {
        auto randPos = mDistribution(mRandomEngine);

        // Erneut "würfeln", wenn bereits eine Miene auf diesem Platz ist
        while(mMineGrid.at(randPos)->isMine())
        {
            randPos = mDistribution(mRandomEngine);
        }

        mMineGrid.at(randPos)->setMine(true);
        //mMineGrid.at(randPos)->setImage(QPixmap(":/resources/mine.png"));
    }
}

// Nachbarn des angegebenen Feldes finden und als vector zurückgeben (Parameter: Spalte, Zeile)
std::vector<MineField *> Game::getNearby(const unsigned int column, const unsigned int row) const
{
    std::vector<MineField*> retVec;

    if(column == 0)
    {
        // 1. Spalte -> nur rechts

        retVec.push_back(mMineGrid.at(row * mColumns + 1));

        if(row == 0)
        {
            // 1. Spalte -> nur rechts
            // 1. Zeile -> nur drunter

            for(int a = 0; a < 2; ++a)
            {
                retVec.push_back(mMineGrid.at(mColumns + a));
            }
        }
        else if(row == mRows - 1)
        {
            // 1. Spalte -> nur rechts
            // letzte. Zeile -> nur drüber

            for(int a = 0; a < 2; ++a)
            {
                retVec.push_back(mMineGrid.at((row - 1) * mColumns + a));
            }
        }
        else
        {
            // 1. Spalte -> nur rechts
            // Zeilen dazwischen -> drüber und drunter

            for(int a = 0; a < 2; ++a)
            {
                // drüber
                retVec.push_back(mMineGrid.at((row - 1) * mColumns + a));

                // drunter
                retVec.push_back(mMineGrid.at((row + 1) * mColumns + a));
            }
        }
    }
    else if(column == mColumns - 1)
    {
        // letzte Spalte -> nur links

        retVec.push_back(mMineGrid.at(column + row * mColumns - 1));

        if(row == 0)
        {
            // letzte. Spalte -> nur links
            // 1. Zeile -> nur drunter

            for(int a = -1; a < 1; ++a)
            {
                retVec.push_back(mMineGrid.at(column + mColumns + a));
            }
        }
        else if(row == mRows - 1)
        {
            // letzte Spalte -> nur links
            // letzte Zeile -> nur drüber

            for(int a = -1; a < 1; ++a)
            {
                retVec.push_back(mMineGrid.at(column + (row - 1) * mColumns + a));
            }
        }
        else
        {
            // letzte Spalte -> nur links
            // Zeilen dazwischen -> drüber und drunter

            for(int a = -1; a < 1; ++a)
            {
                // drüber
                retVec.push_back(mMineGrid.at(column + (row - 1) * mColumns + a));

                // drunter
                retVec.push_back(mMineGrid.at(column + (row + 1) * mColumns + a));
            }
        }
    }
    else
    {
        // Spalten dazwischen -> links und rechts

        retVec.push_back(mMineGrid.at(column + row * mColumns - 1));

        retVec.push_back(mMineGrid.at(column + row * mColumns + 1));

        if(row == 0)
        {
            // 1. Zeile -> nur drunter

            for(int a = -1; a < 2; ++a)
            {
                retVec.push_back(mMineGrid.at(column + mColumns + a));
            }
        }
        else if(row == mRows - 1)
        {
            // letzte Zeile -> nur drüber

            for(int a = -1; a < 2; ++a)
            {
                retVec.push_back(mMineGrid.at(column + (row - 1) * mColumns + a));
            }
        }
        else
        {
            // Zeilen dazwischen -> drüber und drunter

            for(int a = -1; a < 2; ++a)
            {
                // drüber
                retVec.push_back(mMineGrid.at(column + (row - 1) * mColumns + a));

                // drunter
                retVec.push_back(mMineGrid.at(column + (row + 1) * mColumns + a));
            }
        }
    }

    return retVec;
}

// Nachbarn des angegebenen Feldes finden und als vector zurückgeben (Parameter: Index)
std::vector<MineField *> Game::getNearby(const unsigned int index) const
{
    return getNearby(index % mColumns, index / mColumns);
}

// Nachbarn des angegebenen Feldes finden und als vector zurückgeben (Parameter: MineField*)
std::vector<MineField *> Game::getNearby(const MineField * mineField) const
{
    unsigned int index = std::find(mMineGrid.begin(), mMineGrid.end(), mineField) - mMineGrid.begin();

    return getNearby(index);
}

// Anzahl benachbarter Mienen in jeweiligem Feld speichern (Parameter: Spalte, Zeile)
void Game::checkNearbyMines(const unsigned int column, const unsigned int row)
{
    if(mMineGrid.at(column + row * mColumns)->isMine())
    {
        // Wenn Mine, dann zum nächsten Feld gehen

        return;
    }

    unsigned int minesNearby = 0;


    for(const auto& i : std::vector<MineField*>(getNearby(column, row)))
    {
        if(i->isMine())
        {
            ++minesNearby;
        }
    }

    mMineGrid.at(column + row * mColumns)->setMinesNearby(minesNearby);
}

// Anzahl benachbarter Mienen in jeweiligem Feld speichern (Parameter: Index)
void Game::checkNearbyMines(const unsigned int index)
{
    checkNearbyMines(index % mColumns, index / mColumns);
}

// Angegebenes Feld aufdecken (wenn keine benachbarten Mienen -> benachbarte Felder aufdecken)
void Game::searchField(MineField *mineField)
{
    if(mineField->flagState() == MineField::FLAGGED)
    {
        mineField->setFlagState(MineField::NONE);
        --mFlags;
        emit flagRemoved(mMines - mFlags);

        return;
    }

    if(!mineField->isMine())
    {
        mineField->setCleared(true);

        if(!mineField->minesNearby())
        {
            for(const auto& it : getNearby(mineField))
            {
                if(!it->isMine() && !it->cleared())
                {
                    searchField(it);
                }
            }
        }

        // Überprüfe, ob alle Mienen gefunden wurden
        for(const auto& it : mMineGrid)
        {
            if(!it->cleared() && !it->isMine())
            {
                // Noch nicht alle Felder aufgedeckt

                return;
            }
        }

        // Alle Mienen gefunden
        for(const auto& it : mExplosiveFields)
        {
            it->setImage(QPixmap(":/resources/mine.png"));
        }

        // Signal für Spiel gewonnen ausgeben
        emit gameFinished(true);

        // Signal für 0 verbleibende Mienen ausgeben
        emit flagAdded(0);
    }
    else
    {
        // TODO Game Over

        mGameOver = true;

        // Alle Mienen explodieren
        for(const auto& it : mExplosiveFields)
        {
            it->setImage(QPixmap(":/resources/mine_exploded.png"));
        }

        // Signal für Spiel verloren ausgeben
        emit gameFinished(false);
    }
}

// Anzahl platzierter Mienen zurückgeben
unsigned int Game::minesPlaced() const
{
    return mMines;
}

// SLOT | Angeklicktes Feld aufdecken
void Game::slotSearchField()
{
    // Überprüfen, ob Spiel noch läuft
    if(mGameOver)
    {
        // Game Over

        return;
    }

    // Sender des signals ermitteln
    MineField* mineField = qobject_cast <MineField*>(sender());

    // Beim ersten Klick Mienen verteilen
    if(mFirstClick)
    {
        // Auf geklicktes Feld und außenrum Mienen setzen
        mineField->setMine(true);
        for(const auto& it : getNearby(mineField))
        {
            it->setMine(true);
        }

        // Minen verteilen (werden nur auf leere Felder gesetzt)
        spreadMines(mMines);

        // Mienen von geklicktem Feld und dessen Nachbarn löschen
        mineField->setMine(false);
        for(const auto& it : getNearby(mineField))
        {
            it->setMine(false);
        }

        // Felder mit Mienen in extra vector speichern
        for(const auto& it : mMineGrid)
        {
            if(it->isMine())
            {
                mExplosiveFields.push_back(it);
            }
        }
        mExplosiveFields.shrink_to_fit();

        // Anzahl benachbarter Minen ermitteln (für jedes Feld)
        for(unsigned int i = 0; i < mMineGrid.size(); ++i)
        {
            checkNearbyMines(i);
        }

        // Vorteil bei ersten Klick deaktivieren
        mFirstClick = false;

        // Signal für Spielstart ausgeben
        emit gameStarted();
    }

    // Auf geklicktem Feld nach Miene suchen
    searchField(mineField);
}

// SLOT | Angeklicktes Feld mit einer Flagge markieren
void Game::slotFlagMine()
{
    // Überprüfen, ob Spiel noch läuft
    if(mGameOver)
    {
        // Game Over

        return;
    }

    // Sender des Signals ermitteln
    MineField* mineField = qobject_cast <MineField*>(sender());

    // Return, wenn Feld bereits aufgedeckt wurde
    if(mineField->cleared())
    {
        return;
    }

    // Flaggenstatus des geklickten Feldes setzen
    switch(mineField->flagState())
    {
    case MineField::NONE:
        // noch keine Flagge -> Flagge setzen
        mineField->setFlagState(MineField::FLAGGED);
        ++mFlags;
        emit flagAdded(mMines - mFlags);
        break;
    case MineField::FLAGGED:
        // Flagge gesetzt -> als unbekannt markieren
        mineField->setFlagState(MineField::UNKNOWN);
        --mFlags;
        emit flagRemoved(mMines - mFlags);
        break;
    case MineField::UNKNOWN:
        // als unbekannt markiert -> Markierung entfernen
        mineField->setFlagState(MineField::NONE);
        break;
    default:
        break;
    }
}

// EVENT | Fenstergröße ändern
void Game::resizeEvent(QResizeEvent *event)
{
    // TODO

    /*
    // Größe der Felder berechnen
    if(event->size().width() > event->size().height())
    {
        int fieldHeight = (event->size().height() - layout()->spacing() * (mRows - 1)) / mRows;
        mMineFieldSize = QSize(fieldHeight, fieldHeight);
    }
    else
    {
        int fieldWidth = (event->size().width() - layout()->spacing() * (mColumns - 1)) / mColumns;
        mMineFieldSize = QSize(fieldWidth, fieldWidth);
    }

    // Felder auf berechnete Größe skalieren
    for(auto& it : mMineGrid)
    {
        it->setPixmap(it->pixmap().scaled(mMineFieldSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    */

    QString message = "Game Widget size: " + QString::number(width()) + ", " + QString::number(height())
            + " | Field size: " + QString::number(mMineFieldSize.width()) + ", " + QString::number(mMineFieldSize.height())
            + " | Actual field size: " + QString::number(mMineGrid.at(0)->size().width()) + ", " + QString::number(mMineGrid.at(0)->size().height());
    mStatusBar->showMessage(message);

    // Event weitergeben -> unnötig?
    QWidget::resizeEvent(event);
}

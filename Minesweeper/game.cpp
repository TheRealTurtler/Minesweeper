#include "game.h"

// Constructor
Game::Game(const unsigned int columns, const unsigned int rows, const unsigned int mines, QWidget *parent)
    : QWidget(parent), mColumns(columns), mRows(rows), mMines(mines)
{
    //statusBar = new QStatusBar(this);

    // TODO
    // Layout erstellen
    QHBoxLayout* layoutH = new QHBoxLayout;
    QVBoxLayout* layoutV = new QVBoxLayout;
    QGridLayout* gameLayout = new QGridLayout;

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

            mineField->setImage(QPixmap(":/resources/field.png"));
            mineField->setScaledContents( true );
            mineField->setMinimumSize(48, 48);
            //mineField->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

            gameLayout->addWidget(mineField, r, c);

            connect(mineField, &MineField::leftClicked, this, &Game::slotSearchField);
            connect(mineField, &MineField::rightClicked, this, &Game::slotFlagMine);

            mMineGrid.at(c + r * mColumns) = mineField;
        }
    }

    // Abstand zwischen den Feldern festlegen
    gameLayout->setSpacing(4);

    // TODO
    // Spacer im Spielfeld herum hinzufügen
    layoutH->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    layoutH->addLayout(gameLayout);
    layoutH->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    layoutV->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    layoutV->addLayout(layoutH);
    layoutV->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    // Layout anwenden
    this->setLayout(layoutV);

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
    if(!mineField->isMine())
    {
        mineField->setCleared(true);

        switch(mineField->minesNearby())
        {
        case 0:
            for(const auto& it : getNearby(mineField))
            {
                if(!it->isMine() && !it->cleared())
                {
                    searchField(it);
                }
            }

            mineField->setImage(QPixmap(":/resources/empty.png"));
            break;
        case 1:
            mineField->setImage(QPixmap(":/resources/nearby1.png"));
            break;
        case 2:
            mineField->setImage(QPixmap(":/resources/nearby2.png"));
            break;
        case 3:
            mineField->setImage(QPixmap(":/resources/nearby3.png"));
            break;
        case 4:
            mineField->setImage(QPixmap(":/resources/nearby4.png"));
            break;
        case 5:
            mineField->setImage(QPixmap(":/resources/nearby5.png"));
            break;
        case 6:
            mineField->setImage(QPixmap(":/resources/nearby6.png"));
            break;
        case 7:
            mineField->setImage(QPixmap(":/resources/nearby7.png"));
            break;
        case 8:
            mineField->setPixmap(QPixmap(":/resources/nearby8.png"));
            break;
        default:
            break;
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
    }
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
        mineField->setImage(QPixmap(":/resources/flag.png"));
        mineField->setFlagState(MineField::FLAGGED);
        break;
    case MineField::FLAGGED:
        // Flagge gesetzt -> als unbekannt markieren
        mineField->setImage(QPixmap(":/resources/unknown.png"));
        mineField->setFlagState(MineField::UNKNOWN);
        break;
    case MineField::UNKNOWN:
        // als unbekannt markiert -> Markierung entfernen
        mineField->setImage(QPixmap(":/resources/field.png"));
        mineField->setFlagState(MineField::NONE);
        break;
    default:
        break;
    }
}

// EVENT | Fenstergröße ändern
void Game::resizeEvent(QResizeEvent *event)
{
    //statusBar->showMessage(QString::number(this->height()));

    // TODO

    // Größe der Felder berechnen
    if(this->width() > this->height())
    {
        int height = (this->height() - this->layout()->spacing() * (mRows - 1)) / mRows;
        mMineFieldSize = QSize(height, height);
    }
    else
    {
        int width = (this->width() - this->layout()->spacing() * (mColumns - 1)) / mColumns;
        mMineFieldSize = QSize(width, width);
    }

    // Felder auf berechnete Größe skalieren
    for(auto& it : mMineGrid)
    {
        it->setPixmap(it->pixmap().scaled(mMineFieldSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    // Event weitergeben -> unnötig?
    QWidget::resizeEvent(event);
}

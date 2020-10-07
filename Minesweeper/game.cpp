#include "game.h"

// Constructor
Game::Game(QWidget *parent) : QWidget(parent)
{
    // RNG Initialisierung
    std::random_device randomDevice;
    mRandomEngine = std::mt19937(randomDevice());
}

// Constructor mit Spielfeldgröße und Mienenanzahl
Game::Game(const unsigned int columns, const unsigned int rows, const unsigned int mines, QWidget *parent)
    : QWidget(parent)
{
    // RNG Initialisierung
    std::random_device randomDevice;
    mRandomEngine = std::mt19937(randomDevice());

    startGame(columns, rows, mines);
}

// Spielfeld initialisieren
void Game::startGame(const unsigned int columns, const unsigned int rows, const unsigned int mines)
{
    // Variablen definieren
    mFlags = 0;

    mFirstClick = true;
    mGameOver = false;
    mMetalDetector = false;

    // Anzahl Spalten, Zeilen und verteilter Mienen festlegen
    mColumns = columns;
    mRows = rows;
    mMines = mines;

    // Spielfeld leeren
    clearGame();

    // Vectorgröße anpassen
    mMineGrid.resize(mRows * mColumns);
    mMineGrid.shrink_to_fit();

    // Spielfeld erstellen
    for(decltype (mRows) row = 0; row < mRows; ++row)
    {
        for(decltype (mColumns) column = 0; column < mColumns; ++column)
        {
            MineField* mineField = new MineField(this);

            mineField->setMinimumSize(mMineFieldMinimumSize);

            mineField->setGeometry(column * (mMineFieldSize.width() + mSpace), row * (mMineFieldSize.height() + mSpace), mMineFieldSize.width(), mMineFieldSize.height());

            connect(mineField, &MineField::leftClicked, this, &Game::slotSearchField);
            connect(mineField, &MineField::rightClicked, this, &Game::slotFlagMine);

            mMineGrid.at(column + row * mColumns) = mineField;

            mineField->show();
        }
    }

    // Minimale Spielfeldgröße festlegen
    setMinimumSize(mColumns * mMineFieldMinimumSize.width() + (mColumns - 1) * mSpace, mRows * mMineFieldMinimumSize.height() + (mRows - 1) * mSpace);

    // RNG
    mDistribution = std::uniform_int_distribution<size_t>(0, mMineGrid.size() - 1);

    resizeMineFields();
}

// Mienenfelder löschen
void Game::clearGame()
{
    // Spielfeld leeren
    for(auto i : mMineGrid)
    {
        delete i;
    }
}

// Zufällig Mienen auf dem Spielfeld verteilen
void Game::spreadMines(const unsigned int amount)
{
    /*
    // Return wenn mehr Mienen platziert werden sollen, als Felder vorhanden sind
    // -> Redundant, da bereits bei Größenauswahl überprüft
    if(amount > mMineGrid.size())
    {
        return;
    }
    */

    // Vectorgröße der Felder mit Mienen anpassen
    mExplosiveFields.resize(amount);
    mExplosiveFields.shrink_to_fit();

    // Mienen zufällig verteilen
    for(auto i = decltype (amount) {0}; i < amount; ++i)    // auto i = ... weil amount const ist
    {
        auto randPos = mDistribution(mRandomEngine);

        // Erneut "würfeln", wenn bereits eine Miene auf diesem Platz ist
        while(mMineGrid.at(randPos)->isMine())
        {
            randPos = mDistribution(mRandomEngine);
        }

        // Miene auf Feld setzen
        mMineGrid.at(randPos)->setMine(true);

        // Felder mit Mienen in extra vector speichern
        mExplosiveFields.at(i) = mMineGrid.at(randPos);
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
    // Überprüfe, ob dieses Feld bereits untersucht wurde
    if(mineField->cleared())
    {
        return;
    }

    // Überprüfe Flaggenstatus des angegebenen Feldes
    if(mineField->flagState() != MineField::NONE)
    {
        // Return, wenn Miene bereits aufgedeckt wurde
        if(mineField->flagState() == MineField::DETECTED)
        {
            return;
        }

        // Flagge entfernen, wenn eine vorhanden war
        if(mineField->flagState() == MineField::FLAGGED)
        {
            --mFlags;
            emit flagRemoved(mMines - mFlags);
        }

        // Flaggenstatus auf keine Markierung setzen
        mineField->setFlagState(MineField::NONE);
    }

    // Überprüfung, ob KEINE Miene auf dem Feld liegt
    if(!mineField->isMine())
    {
        // Feld als bereits untersucht markieren
        mineField->setCleared(true);

        // Wenn keine benachbarten Mienen -> Nachbarfelder untersuchen
        if(!mineField->minesNearby())
        {
            for(const auto& i : getNearby(mineField))
            {
                if(!i->isMine() && !i->cleared())
                {
                    searchField(i);
                }
            }
        }

        // Überprüfe, ob alle Mienen gefunden wurden
        for(const auto& i : mMineGrid)
        {
            if(!i->cleared() && !i->isMine())
            {
                // Noch nicht alle Felder aufgedeckt

                return;
            }
        }

        // Alle Mienen gefunden
        for(const auto& i : mExplosiveFields)
        {
            i->setImage(QPixmap(":/resources/field.png") ,QPixmap(":/resources/mine.png"));
        }

        mGameOver = true;

        // Signal für Spiel gewonnen ausgeben
        emit gameFinished(true);

        // Signal für 0 verbleibende Mienen ausgeben
        emit flagAdded(0);
    }
    else
    {
        mGameOver = true;

        // Alle Mienen explodieren
        for(const auto& i : mExplosiveFields)
        {
            i->setImage(QPixmap(":/resources/field.png"), QPixmap(":/resources/mine_exploded.png"));
        }

        // Signal für Spiel verloren ausgeben
        emit gameFinished(false);
    }
}

// Cheat / Tipp | Angegebenes Feld auf Mienen untersuchen und diese aufdecken
void Game::detectMine(MineField *mineField)
{
    // Signal für verwendeten Cheat senden
    emit cheated();

    // Überprüfe, ob auf angegebenen Feld eine Miene liegt
    if(mineField->isMine())
    {
        // Signal für gefundene Miene ausgeben
        emit mineDetected(true);

        // Miene aufdecken
        mineField->setFlagState(MineField::DETECTED);
    }
    else
    {
        // Signal für leeres Feld ausgeben
        emit mineDetected(false);

        // Feld normal aufdecken
        searchField(mineField);
    }

    // Metalldetektor wieder ausschalten
    setMetaldetector(false);
}

// Position des Mienenfeldes mit Index index ermitteln
QPoint Game::getFieldPosition(unsigned int index)
{
    QPoint* pos = new QPoint();

    pos->setX((index % mColumns) * (mMineFieldSize.width() + mSpace));
    pos->setY((index / mColumns) * (mMineFieldSize.height() + mSpace));     // int division so gedacht

    return *pos;
}

// Berechnung und Setzen der Größe und Position der Mienenfelder
void Game::resizeMineFields()
{
    int fieldSize;

    // Größe der Felder berechnen
    if(width() > height())
    {
        // Game Widget breiter als hoch

        fieldSize = (height() - mSpace * (mRows - 1)) / mRows;          // int division genau genug
        mMineFieldSize = QSize(fieldSize, fieldSize);
    }
    else
    {
        // Game Widget höher als breit

        fieldSize = (width() - mSpace * (mColumns - 1)) / mColumns;     // int division genau genug
        mMineFieldSize = QSize(fieldSize, fieldSize);
    }

    unsigned int idx = 0;

    // Felder auf berechnete Größe skalieren
    for(const auto& i : mMineGrid)
    {
        i->move(getFieldPosition(idx));
        i->resize(mMineFieldSize);

        ++idx;
    }
}

unsigned int Game::columns() const
{
    return mColumns;
}

unsigned int Game::rows() const
{
    return mRows;
}

// Anzahl platzierter Mienen zurückgeben
unsigned int Game::minesPlaced() const
{
    return mMines;
}

// Metalldetektorstatus zurückgeben (Cheat / Tipp um nach Mienen zu suchen)
bool Game::metalDetector() const
{
    return mMetalDetector;
}

// Metalldetektorstatus setzen (Cheat / Tipp um nach Mienen zu suchen)
void Game::setMetaldetector(bool metalDetector)
{
    // Return, wenn mMetalDetector bereits den Wert von metalDetector hat
    if(mMetalDetector == metalDetector)
    {
        return;
    }

    mMetalDetector = metalDetector;

    // Cursor ändern
    if(mMetalDetector)
    {
        QCursor cursor(QPixmap(":/resources/metal_detector.png"), 0, 0);

        setCursor(cursor);
    }
    else
    {
        unsetCursor();
    }
}

// SLOT | Angeklicktes Feld aufdecken
void Game::slotSearchField()
{
    // Überprüfen, ob Spiel noch läuft
    if(mGameOver)
    {
        // Metalldetektor ausschalten
        if(mMetalDetector)
        {
            setMetaldetector(false);
        }

        return;
    }

    // Sender des signals ermitteln
    MineField* mineField = qobject_cast <MineField*>(sender());

    // Wenn Feld als Miene oder unbekannt markiert -> Markierung entfernen
    if(mineField->flagState() != MineField::NONE)
    {
        // Return, wenn Miene bereits aufgedeckt wurde
        if(mineField->flagState() == MineField::DETECTED)
        {
            return;
        }

        // Flagge entfernen, wenn eine vorhanden war
        if(mineField->flagState() == MineField::FLAGGED)
        {
            --mFlags;
            emit flagRemoved(mMines - mFlags);
        }

        // Flaggenstatus auf keine Markierung setzen
        mineField->setFlagState(MineField::NONE);

        return;
    }

    // Beim ersten Klick Mienen verteilen
    if(mFirstClick)
    {
        // Auf geklicktes Feld und außenrum Mienen setzen
        mineField->setMine(true);
        for(const auto& i : getNearby(mineField))
        {
            i->setMine(true);
        }

        // Minen verteilen (werden nur auf leere Felder gesetzt)
        spreadMines(mMines);

        // Mienen von geklicktem Feld und dessen Nachbarn löschen
        mineField->setMine(false);
        for(const auto& it : getNearby(mineField))
        {
            it->setMine(false);
        }

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

    // Überprüfe Metalldetektorstatus (Cheat / Tipp)
    if(mMetalDetector)
    {
        // Miene aufdecken
        detectMine(mineField);
    }
    else
    {
        // Auf geklicktem Feld nach Miene suchen und Felder aufdecken
        searchField(mineField);
    }
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

// EVENT | Größe geändert
void Game::resizeEvent(QResizeEvent *event)
{
    // Wenn resizeEvent aufgerufen wird, hat das Widget bereits seine neue Größe
    // -> kann einfach width(), height() verwenden

    if(event->oldSize() != size())
    {
        resizeMineFields();

        /*
        QString message = "Game Widget size: " + QString::number(width()) + ", " + QString::number(height())
                + " | Field size: " + QString::number(mMineFieldSize.width()) + ", " + QString::number(mMineFieldSize.height())
                + " | Actual field size: " + QString::number(mMineGrid.at(0)->size().width()) + ", " + QString::number(mMineGrid.at(0)->size().height())
                + " | idx :" + QString::number(idx);
        mStatusBar->showMessage(message);
        */

        return;
    }

    // Event weitergeben
    return QWidget::resizeEvent(event);
}

// EVENT | Maustaste gedrückt
void Game::mousePressEvent(QMouseEvent *event)
{
    const auto& button = event->button();

    // Metalldetektor zurücksetzen, wenn kein Mienenfeld angeklickt wurde
    if(button == Qt::LeftButton || button == Qt::RightButton)
    {
        setMetaldetector(false);

        return;
    }

    return QWidget::mousePressEvent(event);
}

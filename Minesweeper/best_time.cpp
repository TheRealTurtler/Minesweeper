#include "best_time.h"

BestTime::BestTime(QWidget *parent) : QWidget(parent)
{
    //Layout erstellen
    auto layout = new QVBoxLayout(this);

    // Labels erstellen
    auto label = new QLabel("Bestzeit:", this);
    mBestTimeLabel = new QLabel("--:--", this);

    // Labelausrichtuing festlegen
    label->setAlignment(Qt::AlignHCenter);
    mBestTimeLabel->setAlignment(Qt::AlignHCenter);

    // Labels zu Layout hinzufügen
    layout->addWidget(label);
    layout->addWidget(mBestTimeLabel);
}

void BestTime::displayBestTime(unsigned int columns, unsigned int rows, unsigned int mines)
{
    // Dateipfad festlegen
    QString path = QDir::currentPath();
    path.append("/best_times.txt");

    // Datei öffnen
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // Datei konnte nicht geöffnet werden       // TODO
        return;
    }

    bool bestTimeFound = false;

    // Datei einlesen
    QTextStream inStream(&file);
    while(!inStream.atEnd())
    {
        QString line = inStream.readLine();

        // Nach gegebener Spielfeldgröße suchen
        if(line.contains(QString("%1x%2x%3").arg(columns).arg(rows).arg(mines)))
        {
            bestTimeFound = true;

            break;
        }
    }

    QString bestTime;

    if(bestTimeFound)
    {
        // Wenn Datei noch nicht zu ende, nächste zeile einlesen und als Zeit anzeigen
        if(!inStream.atEnd())
        {
            bestTime = inStream.readLine();

            auto list = bestTime.split(':');

            mMinutes = list.at(0).toUInt();
            mSeconds = list.at(1).toUInt();

            mBestTimeAvailable = true;
        }
        else
        {
            bestTime = "--:--";

            mBestTimeAvailable = false;
        }
    }
    else
    {
        bestTime = "--:--";

        mBestTimeAvailable = false;
    }

    // Bestzeit anzeigen
    mBestTimeLabel->setText(bestTime);

    // Datei schließen
    file.close();
}

void BestTime::saveBestTime(unsigned int columns, unsigned int rows, unsigned int mines, unsigned int minutes, unsigned int seconds)
{
    // Dateipfad festlegen
    QString path = QDir::currentPath();
    path.append("/best_times.txt");

    // Datei öffnen
    QFile file(path);

    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        // Datei konnte nicht geöffnet werden       // TODO
        return;
    }

    bool sizeFound = false;

    // Datei einlesen
    QTextStream ioStream(&file);

    while(!ioStream.atEnd())
    {
        QString line = ioStream.readLine();

        // Nach gegebener Spielfeldgröße suchen
        if(line.contains(QString("%1x%2x%3").arg(columns).arg(rows).arg(mines)))
        {
            sizeFound = true;

            break;
        }
    }

    if(!sizeFound)
    {
        ioStream << QString("[%1x%2x%3]").arg(columns).arg(rows).arg(mines) << Qt::endl;
    }

    // Cursor an aktuelle Position setzen
    ioStream.seek(ioStream.pos());

    QString bestTime = QString("%1:%2").arg(minutes, 2, 10, QLatin1Char('0')).arg(seconds, 2, 10, QLatin1Char('0'));

    // Bestzeit in Datei schreiben
    ioStream << bestTime << Qt::endl << Qt::endl;

    // Datei schließen
    file.close();
}

unsigned int BestTime::minutes() const
{
    return mMinutes;
}

unsigned int BestTime::seconds() const
{
    return mSeconds;
}

unsigned int BestTime::totalSeconds() const
{
    return mMinutes * 60 + mSeconds;
}

bool BestTime::available() const
{
    return mBestTimeAvailable;
}

#ifndef MINEFIELD_H
#define MINEFIELD_H

#include <QLabel>
#include <QPixmap>
#include <QMouseEvent>

class MineField : public QLabel
{
    Q_OBJECT

public:
    explicit MineField(QWidget* parent = nullptr);

    enum FlagState
    {
        NONE,
        FLAGGED,
        UNKNOWN
    };

    // Get und Set Funktionen
    bool isMine();
    void setMine(bool isMine);
    bool cleared();
    void setCleared(bool cleared);
    unsigned short minesNearby();
    void setMinesNearby(unsigned short minesNearby);
    QPixmap pixmap();
    void setImage(const QPixmap& pixmap);
    void setImage(const QPixmap& basePixmap, const QPixmap& overlayPixmap);
    FlagState flagState();
    void setFlagState(FlagState flagState);

signals:
    void leftClicked();
    void rightClicked();

protected:
   virtual void mousePressEvent(QMouseEvent* event) override;
   virtual void resizeEvent(QResizeEvent* event) override;

private:
   bool mIsMine = false;
   bool mCleared = false;
   FlagState mFlagState = NONE;
   unsigned short mMinesNearby = 0;

   QPixmap mPixmap;
};

#endif // MINEFIELD_H

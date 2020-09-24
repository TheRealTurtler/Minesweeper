#ifndef CLICKABLE_LABEL_H
#define CLICKABLE_LABEL_H

#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include <QResizeEvent>

class ClickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickableLabel(QWidget* parent = nullptr);

    // Get und Set Funktionen
    QPixmap originalPixmap();
    void setImage(const QPixmap& pixmap);
    void setImage(const QPixmap& basePixmap, const QPixmap& overlayPixmap);

signals:
    void clicked();

protected:
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void ClickableLabel::resizeEvent(QResizeEvent *event) override;

private:
    QPixmap mPixmap;
};

#endif // CLICKABLE_LABEL_H

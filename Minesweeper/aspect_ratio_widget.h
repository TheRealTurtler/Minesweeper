#ifndef ASPECT_RATIO_WIDGET_H
#define ASPECT_RATIO_WIDGET_H

#include <QWidget>
#include <QBoxLayout>
#include <QResizeEvent>

// Diese Klasse wurde unter Zuhilfenahme von https://stackoverflow.com/a/30008442 erstellt

class AspectRatioWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AspectRatioWidget(QWidget* widget, float aspectRatio, QWidget *parent = nullptr);
    explicit AspectRatioWidget(QWidget* widget, float width, float height, QWidget *parent = nullptr);

    void stretchLayout();

    // Get und Set Funktionen
    void setAspectRatio(float aspectRatio);
    void setAspectRatio(float width, float height);

signals:

protected:
    virtual void resizeEvent(QResizeEvent* event) override;

private:
    float mAspectRatio = 1;

    QBoxLayout* mLayout = nullptr;
};

#endif // ASPECTRATIO_H

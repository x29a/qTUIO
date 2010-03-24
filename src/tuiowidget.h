#ifndef TUIOWIDGET_H
#define TUIOWIDGET_H

#include <QWidget>
#include <QEvent>
#include <QDebug>
#include <QPainter>

class TUIOWidget : public QWidget
{
    Q_OBJECT

public:
    TUIOWidget();

    bool createImage();

    void resizeImage(QImage *image, const QSize &newSize);

    int getWidth(void);
    int getHeight(void);


protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    bool event(QEvent *event);



private:
    QList<QColor> myPenColors;
    QImage image;
    int wHeight;
    int wWidth;

};

#endif // TUIOWIDGET_H

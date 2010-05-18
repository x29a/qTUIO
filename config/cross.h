#ifndef CROSS_H
#define CROSS_H

#include <QGraphicsRectItem>

class Cross : public QGraphicsRectItem
{
public:
    Cross();
    bool sceneEvent(QEvent *event);

private:
    QGraphicsRectItem *lr;
    QPoint offset;
    int x;
    int y;
    int cnt;
    int processConfig();
};

#endif // CROSS_H

#ifndef TUIOWIDGET_H
#define TUIOWIDGET_H

#include <QWidget>
#include <QEvent>
#include <QDebug>

class TUIOWidget : public QWidget
{
    Q_OBJECT

public:
    TUIOWidget();

public slots:
    void buttonTriggered();
    bool event(QEvent *event);

};

#endif // TUIOWIDGET_H

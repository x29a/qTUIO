#ifndef TUIOWIDGET_H
#define TUIOWIDGET_H

#include <QWidget>

class TUIOWidget : public QWidget
{
    Q_OBJECT

public:
    TUIOWidget();

public slots:
    void buttonTriggered();

};

#endif // TUIOWIDGET_H

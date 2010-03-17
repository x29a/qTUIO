#ifndef TUIOBUTTON_H
#define TUIOBUTTON_H

#include <QPushButton>

class TuioButton : public QPushButton
{
public:
    TuioButton(QWidget *parent = 0);

public slots:
    void on_click();
};

#endif // TUIOBUTTON_H

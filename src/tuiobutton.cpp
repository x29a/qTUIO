#include "tuiobutton.h"

TuioButton::TuioButton(QWidget *parent) :
    QPushButton(parent)
{
    setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum);

    // Activating this option, will make the widget receive TouchEvents
    // If not set, touch events will be handled has Mouse events
    //setAttribute( Qt::WA_AcceptTouchEvents );

    connect(this, SIGNAL(clicked()), this, SLOT(on_click()));
}


void TuioButton::on_click()
{
    static int n_clicks = 0;

    setText(QString::number(n_clicks++));
}

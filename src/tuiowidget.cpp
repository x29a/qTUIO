#include "tuiowidget.h"
#include "tuiobutton.h"
#include <QGridLayout>

TUIOWidget::TUIOWidget()
{
    setWindowState(Qt::WindowFullScreen);

    QGridLayout *grid = new QGridLayout(this);
    setLayout(grid);

    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 4; k++) {
            TuioButton *button = new TuioButton();

            button->setText( QString("Button %1 %2").arg(i).arg(k) );

            grid->addWidget(button, i, k );
        }
    }



}


void TUIOWidget::buttonTriggered()
{

}

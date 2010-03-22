#include "tuiowidget.h"
#include "tuiobutton.h"
#include <QGridLayout>
#include <QList>
#include <QTouchEvent>

TUIOWidget::TUIOWidget()
{
    setWindowState(Qt::WindowFullScreen);
	setAttribute(Qt::WA_AcceptTouchEvents);

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

bool TUIOWidget::event(QEvent *event){
	if(event->type() == QEvent::TouchBegin) {
		qDebug() << "widget TouchBegin detected";
		QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
		foreach (const QTouchEvent::TouchPoint &touchPoint, touchPoints) {
			qDebug() << "pos" << touchPoint.screenPos();
		}
	}
	else
	{
		//qDebug() << "widget event detected";
	}
	//return false;
	return QWidget::event(event);
}

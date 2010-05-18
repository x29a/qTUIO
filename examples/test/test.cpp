#include "test.h"

#include <QEvent>
#include <QTouchEvent>
#include <QDebug>

Test::Test(void)
{
	qDebug() << "constructor";
}

Test::~Test(void)
{
	qDebug() << "destructor";
}

bool Test::event(QEvent *event)
{
	qDebug() << "event detected: " << event->type();
	switch (event->type()) {
	case QEvent::TouchBegin:
	case QEvent::TouchUpdate:
	case QEvent::TouchEnd:
	{
		qDebug() << "MT event detected";
		/*
		int countTouchPoints=0;
		QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
		foreach (const QTouchEvent::TouchPoint &touchPoint, touchPoints)
		{
			countTouchPoints++;
		}
		qDebug() << "countTouchPoints: " << countTouchPoints;
		break;
		*/
	}
	default:
		return QWidget::event(event);
	}

	return true;
}

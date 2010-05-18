/****************************************************************************
 **
 ** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 ** All rights reserved.
 ** Contact: Nokia Corporation (qt-info@nokia.com)
 **
 ** This file is part of the examples of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:LGPL$
 ** Commercial Usage
 ** Licensees holding valid Qt Commercial licenses may use this file in
 ** accordance with the Qt Commercial License Agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and Nokia.
 **
 ** GNU Lesser General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU Lesser
 ** General Public License version 2.1 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.LGPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU Lesser General Public License version 2.1 requirements
 ** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 **
 ** In addition, as a special exception, Nokia gives you certain additional
 ** rights.  These rights are described in the Nokia Qt LGPL Exception
 ** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
 **
 ** GNU General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU
 ** General Public License version 3.0 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.GPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU General Public License version 3.0 requirements will be
 ** met: http://www.gnu.org/copyleft/gpl.html.
 **
 ** If you have questions regarding the use of this file, please contact
 ** Nokia at qt-info@nokia.com.
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

#include "knob.h"

#define DEBUG

#include <QBrush>
#include <QTouchEvent>
#include <QGraphicsWidget>
#ifdef DEBUG
#include <QtDebug>
#endif

#include <QGraphicsView>

#define SQRT2 1.4142135623730950488016887


Knob::Knob()
: QGraphicsEllipseItem(-50, -50, 100, 100)
{
	setAcceptTouchEvents(true);
	setBrush(Qt::lightGray);

	QGraphicsEllipseItem *leftItem = new QGraphicsEllipseItem(0, 0, 20, 20, this);
	leftItem->setPos(-40, -10);
	leftItem->setBrush(Qt::darkGreen);

	QGraphicsEllipseItem *rightItem = new QGraphicsEllipseItem(0, 0, 20, 20, this);
	rightItem->setPos(20, -10);
	rightItem->setBrush(Qt::darkRed);
}

bool Knob::sceneEvent(QEvent *event)
{
	switch (event->type()) {
	case QEvent::TouchBegin:
	case QEvent::TouchUpdate:
	case QEvent::TouchEnd:
	{
		qDebug() << "touchevent received";
		QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
		const QTouchEvent::TouchPoint &touchPoint1 = touchEvent->touchPoints().first();
		const QTouchEvent::TouchPoint &touchPoint2 = touchEvent->touchPoints().last();
		if (QLineF(touchPoint2.screenPos(), touchPoint2.lastScreenPos()).length() >= SQRT2)
			if (touchEvent->touchPoints().length() == 2) { // scale & rotate
				QLineF line1(touchPoint1.lastScenePos(), touchPoint2.lastScenePos());
				QLineF line2(touchPoint1.scenePos(), touchPoint2.scenePos());
				qreal r = line2.angleTo(line1);
				while (r + this->rotation() > 180)
					r -= 360;
				while (r + this->rotation() < -180)
					r += 360;
				this->setRotation(this->rotation() + r);
				qreal s = (line2.length()+80)/(line1.length()+80) - 1.0;
				if (this->scale() + s >= 0.75 && this->scale() + s <= 3)
					this->setScale(this->scale() + s);
				QPointF d = touchPoint2.scenePos() - touchPoint1.scenePos();
				this->setPos(touchPoint2.scenePos()-d/2);
			} else if (touchEvent->touchPoints().length() == 1) { // move
				QPointF d = touchPoint2.scenePos() - touchPoint2.lastScenePos();
				if (this->scene()->sceneRect().contains(this->pos()+d))
					this->setPos(this->pos() + d);
			}
		break;
	}
	default:
		return QGraphicsItem::sceneEvent(event);
	}
	//     qDebug() << this->pos() << "\tScale: " << this->scale() << "\tRotation: " << this->rotation();
	return true;
}

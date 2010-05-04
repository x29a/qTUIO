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

//#define DEBUG

 #include <QBrush>
 #include <QTouchEvent>

#ifdef DEBUG
#include <QtDebug>
#endif



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
#ifdef DEBUG
     QString typ;
     switch (event->type()) {
     case QEvent::TouchBegin: {
             typ = "TouchBegin ";
             typ += QString::number(static_cast<QTouchEvent *>(event)->touchPoints().first().id());
             break;
         }
     case QEvent::TouchUpdate: {
             typ = "TouchUpdate ";
             typ += QString::number(static_cast<QTouchEvent *>(event)->touchPoints().first().id());
             break;
         }
     case QEvent::TouchEnd: {
             typ = "TouchEnd ";
             typ += QString::number(static_cast<QTouchEvent *>(event)->touchPoints().first().id());
             break;
         }
     default: {
             typ = "Non-TouchEvent";
         }
     }
#endif
     switch (event->type()) {
     case QEvent::TouchBegin:
     case QEvent::TouchUpdate:
     case QEvent::TouchEnd:
     {

         QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
#ifdef DEBUG
         qDebug() << "!!! Touch Event received !!! " << typ;
         qDebug() << "First ID: " << touchEvent->touchPoints().first().id() << " , first SCENEPOS: " << touchEvent->touchPoints().first().scenePos() << " , first POS: " << touchEvent->touchPoints().first().pos();
         qDebug() << "Last ID: " << touchEvent->touchPoints().last().id() << " , last SCENEPOS: " << touchEvent->touchPoints().last().scenePos() << " , last POS: " << touchEvent->touchPoints().last().pos();
#endif

         if (touchEvent->touchPoints().count() == 2) {
             const QTouchEvent::TouchPoint &touchPoint1 = touchEvent->touchPoints().first();
             const QTouchEvent::TouchPoint &touchPoint2 = touchEvent->touchPoints().last();

             QLineF line1(touchPoint1.lastScenePos(), touchPoint2.lastScenePos());
             QLineF line2(touchPoint1.scenePos(), touchPoint2.scenePos());

             rotate(line2.angleTo(line1));
         }

         break;
     }

     default:
         return QGraphicsItem::sceneEvent(event);
     }

     return true;
 }

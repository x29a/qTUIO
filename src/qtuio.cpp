/*
	qTUIO - TUIO Interface for Qt

	Original Version by Martin Blankenburg <martin.blankenburg@imis.uni-luebeck.de>
	Integrated into qTUIO by x29a <0.x29a.0@gmail.com>

	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "qtuio.h"

#include <QEvent>
#include <QTouchEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsWidget>
#include <QMainWindow>

#include <QtDebug>

#include "TuioClient.h"
#include "TuioCursor.h"

#ifdef WIN32
#define OFFSETX 5
#define OFFSETY 35
#else
#define OFFSETX 0
#define OFFSETY 0
#endif

QTuio::QTuio(QObject *parent)
{
    theMainWindow = qobject_cast<QMainWindow *>(parent);
    theView = qobject_cast<QGraphicsView *>(parent);
    if (theView)
        theScene = theView->scene();
    else
        theScene = qobject_cast<QGraphicsScene *>(parent);
}

QTuio::~QTuio()
{
    if (running) {
        tuioClient->disconnect();
        delete tuioClient;
        delete qTouchPointMap;
        running = false;
        wait();
    }
}


void QTuio::run()
{
    running = true;
    screenRect = QApplication::desktop()->rect();
    tuioClient = new TUIO::TuioClient::TuioClient(3333);
    tuioClient->addTuioListener(this);
    tuioClient->connect();
    qTouchPointMap = new QMap<int, QTouchEvent::TouchPoint>();
}


void QTuio::addTuioObject(TUIO::TuioObject *tobj) {}

void QTuio::updateTuioObject(TUIO::TuioObject *tobj) {}

void QTuio::removeTuioObject(TUIO::TuioObject *tobj) {}


bool QTuio::tuioToQt(TUIO::TuioCursor *tcur, QEvent::Type eventType)
{
    const QPointF normPos(tcur->getX(), tcur->getY());
    const QPointF screenPos(screenRect.width() * normPos.x() - OFFSETX, screenRect.height() * normPos.y() - OFFSETY);

    QTouchEvent::TouchPoint touchPoint(tcur->getSessionID());

    touchPoint.setNormalizedPos(normPos);
    touchPoint.setRect(QRectF());

    touchPoint.setPressure(1.0);
    touchPoint.setScreenRect(screenRect);
    touchPoint.setScreenPos(screenPos);

    if (theScene) {
        touchPoint.setSceneRect(theScene->sceneRect());
        if (theView) {
            const QPoint pos((int)screenPos.x() - theView->geometry().x(),
                             (int)screenPos.y() - theView->geometry().y());
            touchPoint.setPos(pos);
            touchPoint.setScenePos(theView->mapToScene(pos));
        } else {
            foreach (QGraphicsView *view, theScene->views()) {
                if (view->isActiveWindow()) {
                    const QPoint pos((int)screenPos.x() - view->geometry().x(),
                                     (int)screenPos.y() - view->geometry().y());
                    touchPoint.setPos(pos);
                    touchPoint.setScenePos(view->mapToScene(pos));
                }
            }
        }
    } else {
        const QPoint pos((int)screenPos.x() - theMainWindow->geometry().x(),
                         (int)screenPos.y() - theMainWindow->geometry().y());
        touchPoint.setPos(pos);
        touchPoint.setSceneRect(QRectF());
        touchPoint.setScenePos(pos);
    }

    Qt::TouchPointStates touchPointStates;

    switch (eventType) {
    case QEvent::TouchBegin: {
	    touchPointStates = Qt::TouchPointPressed;

            touchPoint.setState(Qt::TouchPointPressed);
            touchPoint.setStartNormalizedPos(normPos);
            touchPoint.setStartPos(touchPoint.pos());
            touchPoint.setStartScreenPos(screenPos);
            touchPoint.setStartScenePos(touchPoint.scenePos());

            touchPoint.setLastNormalizedPos(normPos);
            touchPoint.setLastPos(touchPoint.pos());
            touchPoint.setLastScreenPos(screenPos);
            touchPoint.setLastScenePos(touchPoint.scenePos());

            qTouchPointMap->insert(tcur->getSessionID(), touchPoint);
            break;
        }
    case QEvent::TouchUpdate: {
            if (tcur->getMotionSpeed() > 0)
	    {
                touchPointStates = Qt::TouchPointMoved;

                touchPoint.setState(Qt::TouchPointMoved);
	    }
            else
	    {
                touchPointStates = Qt::TouchPointStationary;

                touchPoint.setState(Qt::TouchPointStationary);
	    }

            touchPoint.setStartNormalizedPos(qTouchPointMap->value(tcur->getSessionID()).startNormalizedPos());
            touchPoint.setStartPos(qTouchPointMap->value(tcur->getSessionID()).startPos());
            touchPoint.setStartScreenPos(qTouchPointMap->value(tcur->getSessionID()).startScreenPos());
            touchPoint.setStartScenePos(qTouchPointMap->value(tcur->getSessionID()).startScenePos());

            touchPoint.setLastNormalizedPos(qTouchPointMap->value(tcur->getSessionID()).normalizedPos());
            touchPoint.setLastPos(qTouchPointMap->value(tcur->getSessionID()).pos());
            touchPoint.setLastScreenPos(qTouchPointMap->value(tcur->getSessionID()).screenPos());
            touchPoint.setLastScenePos(qTouchPointMap->value(tcur->getSessionID()).scenePos());

            qTouchPointMap->insert(tcur->getSessionID(), touchPoint);
            break;
        }
    case QEvent::TouchEnd: {
            touchPointStates = Qt::TouchPointReleased;

            touchPoint.setState(Qt::TouchPointReleased);

            touchPoint.setStartNormalizedPos(qTouchPointMap->value(tcur->getSessionID()).startNormalizedPos());
            touchPoint.setStartPos(qTouchPointMap->value(tcur->getSessionID()).startPos());
            touchPoint.setStartScreenPos(qTouchPointMap->value(tcur->getSessionID()).startScreenPos());
            touchPoint.setStartScenePos(qTouchPointMap->value(tcur->getSessionID()).startScenePos());

            touchPoint.setLastNormalizedPos(qTouchPointMap->value(tcur->getSessionID()).normalizedPos());
            touchPoint.setLastPos(qTouchPointMap->value(tcur->getSessionID()).pos());
            touchPoint.setLastScreenPos(qTouchPointMap->value(tcur->getSessionID()).screenPos());
            touchPoint.setLastScenePos(qTouchPointMap->value(tcur->getSessionID()).scenePos());

            qTouchPointMap->insert(tcur->getSessionID(), touchPoint);
            break;
        }
    default: {}
    }

    QEvent *touchEvent = new QTouchEvent(eventType, QTouchEvent::TouchScreen, Qt::NoModifier, touchPointStates, qTouchPointMap->values());

/**********************************************************
 * Old Code doesn't work with QGraphicsView
 * it doesn't send events to the viewport
 * and which make the pinchzoom example doesn't work
***********************************************************/
/*    if (theScene)
        qApp->postEvent(theScene, touchEvent);
    else if (theView)
        qApp->postEvent(theView->scene(), touchEvent);
    else
        qApp->postEvent(theMainWindow->centralWidget(), touchEvent);*/

/************************************************
 * New code fixing the issue with QGraphicsViw
*************************************************/
    if (theView && theView->viewport())
        qApp->postEvent(theView->viewport(), touchEvent);
    else if (theScene)
        qApp->postEvent(theScene, touchEvent);
    else
        qApp->postEvent(theMainWindow->centralWidget(), touchEvent);


    if (eventType == QEvent::TouchEnd)
        qTouchPointMap->remove(tcur->getSessionID());

    return true;
}


void QTuio::addTuioCursor(TUIO::TuioCursor *tcur)
{
	QTuio::tuioToQt(tcur, QEvent::TouchBegin);
}

void QTuio::updateTuioCursor(TUIO::TuioCursor *tcur)
{
	QTuio::tuioToQt(tcur, QEvent::TouchUpdate);
}

void QTuio::removeTuioCursor(TUIO::TuioCursor *tcur)
{
	QTuio::tuioToQt(tcur, QEvent::TouchEnd);
}


void  QTuio::refresh(TUIO::TuioTime frameTime) {}

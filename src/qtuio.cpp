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

#include <QDomDocument>
#include <QDomElement>
#include <QTextStream>
#include <QProcessEnvironment>

QPoint offset(0, 0);

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


int QTuio::processConfig(QFile *file)
{
    QDomDocument doc("qTUIOconfig");
    if (!doc.setContent(file))
        return -1;
    QDomElement root = doc.documentElement();
    if (root.tagName() != "CONFIG")
        return -2;
    if (root.attribute("CONFIGURED", "") != "TRUE") {
        qDebug() << "qTUIO not yet configured, using default values";
        return -3;
    } else {
        QDomNode n = root.firstChild();
        while (!n.isNull()) {
          QDomElement e = n.toElement();
          if (!e.isNull()) {
            if (e.tagName() == "OFFSET") {
                offset.setX(e.attribute("X", "0").toInt());
                offset.setY(e.attribute("Y", "0").toInt());
            }
          }
          n = n.nextSibling();
        }
    }
    return 0;
}



void QTuio::run()
{
    running = true;
    screenRect = QApplication::desktop()->rect();
    tuioClient = new TUIO::TuioClient::TuioClient(3333);
    tuioClient->addTuioListener(this);
    tuioClient->connect();
    qTouchPointMap = new QMap<int, QTouchEvent::TouchPoint>();

    QString home = QProcessEnvironment::systemEnvironment().value("HOME");
    QFile file(home.append("/.qtuioconfig"));
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTuio::processConfig(&file);
        file.close();
    } else {
        qDebug() << "Configuration file not found, using default values";
    }
}


void QTuio::addTuioObject(TUIO::TuioObject *tobj) {}

void QTuio::updateTuioObject(TUIO::TuioObject *tobj) {}

void QTuio::removeTuioObject(TUIO::TuioObject *tobj) {}


bool QTuio::tuioToQt(TUIO::TuioCursor *tcur, QEvent::Type eventType)
{
    QTouchEvent::TouchPoint touchPoint(tcur->getSessionID());

    const QPointF normPos(tcur->getX(), tcur->getY());
    const QPointF screenPos(screenRect.width() * normPos.x() - offset.x(), screenRect.height() * normPos.y() - offset.y());

    touchPoint.setRect(QRectF());
    touchPoint.setNormalizedPos(normPos);

    touchPoint.setPressure(1.0);
    touchPoint.setScreenRect(QRectF());
    touchPoint.setScreenPos(screenPos);

    touchPoint.setSceneRect(QRectF());

    if (theScene) {
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
        touchPoint.setScenePos(pos);
    }

    switch (eventType) {
    case QEvent::TouchBegin: {
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
            if (tcur->getMotionSpeed() > 0 && tcur->getMotionAccel() > 0)
                touchPoint.setState(Qt::TouchPointMoved);
            else
                touchPoint.setState(Qt::TouchPointStationary);

            touchPoint.setLastNormalizedPos(qTouchPointMap->value(tcur->getSessionID()).normalizedPos());
            touchPoint.setLastPos(qTouchPointMap->value(tcur->getSessionID()).pos());
            touchPoint.setLastScreenPos(qTouchPointMap->value(tcur->getSessionID()).screenPos());
            touchPoint.setLastScenePos(qTouchPointMap->value(tcur->getSessionID()).scenePos());

            qTouchPointMap->insert(tcur->getSessionID(), touchPoint);
            break;
        }
    case QEvent::TouchEnd: {
            touchPoint.setState(Qt::TouchPointReleased);

            touchPoint.setLastNormalizedPos(qTouchPointMap->value(tcur->getSessionID()).normalizedPos());
            touchPoint.setLastPos(qTouchPointMap->value(tcur->getSessionID()).pos());
            touchPoint.setLastScreenPos(qTouchPointMap->value(tcur->getSessionID()).screenPos());
            touchPoint.setLastScenePos(qTouchPointMap->value(tcur->getSessionID()).scenePos());
            break;
        }
    default: {}
    }

    QList<QTouchEvent::TouchPoint> touchPointList;
    if (theScene) {
        QGraphicsItem *tpItem;
        QGraphicsItem *touchPointItem;
        foreach (QTouchEvent::TouchPoint tp, qTouchPointMap->values()) {
            tpItem = theScene->itemAt(tp.scenePos());
            touchPointItem = theScene->itemAt(touchPoint.scenePos());
            if (tp.id() != touchPoint.id() && tpItem && touchPointItem && tpItem == touchPointItem) {
                touchPointList.append(tp);
            }
        }
    }
    else {
        QWidget *tpWidget;
        QWidget *touchPointWidget;
        foreach (QTouchEvent::TouchPoint tp, qTouchPointMap->values()) {
            tpWidget = theMainWindow->childAt(tp.scenePos().x(), tp.scenePos().y());
            touchPointWidget = theMainWindow->childAt(touchPoint.scenePos().x(), touchPoint.scenePos().y());
            if (tp.id() != touchPoint.id() && tpWidget && touchPointWidget && tpWidget == touchPointWidget) {
                touchPointList.append(tp);
            }
        }
    }
    touchPointList.append(touchPoint);

    QEvent::Type touchEventType = eventType;
    if (touchPointList.length() != 1)
        touchEventType = QEvent::TouchUpdate;

    QEvent *touchEvent = new QTouchEvent(touchEventType, QTouchEvent::TouchScreen, Qt::NoModifier, 0, QList<QTouchEvent::TouchPoint>()<<touchPointList);
    if (theScene)
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

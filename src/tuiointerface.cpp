
#include "tuiointerface.h"


#include <QApplication>
#include <QDesktopWidget>
#include <QEvent>
#include <QObject>

void TUIOinterface::setTarget(QObject *target){
	this->target=target;
}


TUIOinterface::TUIOinterface() :
    TuioListener()
{
	this->target = 0;
    int port = 3333;
    _client = new TuioClient(port);
    _client->addTuioListener(this);

    QDesktopWidget desktop;

    _screenHeight = desktop.screenGeometry().height();
    _screenWidth = desktop.screenGeometry().width();

}

TUIOinterface::~TUIOinterface()
{
    if (_client->isConnected())
    {
        _client->disconnect();
    }

    delete _client;
	// stub
}

void TUIOinterface::start()
{


    qDebug() << "started";


    _client->connect();
}

void TUIOinterface::addTuioObject(TuioObject *tobj)
{
    qDebug() << tobj->getSymbolID() << " (" << tobj->getSessionID() << ") "<< tobj->getX() << " " << tobj->getY() << " " << tobj->getAngle() ;
}

void TUIOinterface::updateTuioObject(TuioObject *tobj)
{
    qDebug() << "set obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ") "<< tobj->getX() << " " << tobj->getY() << " " << tobj->getAngle()
                << " " << tobj->getMotionSpeed() << " " << tobj->getRotationSpeed() << " " << tobj->getMotionAccel() << " " << tobj->getRotationAccel();
}

void TUIOinterface::removeTuioObject(TuioObject *tobj)
{
    qDebug()  << "del obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ")";
}

/*!
    Triggers a touch event

*/
void TUIOinterface::addTuioCursor(TuioCursor *tcur)
{
	/*
    QTouchEvent *t;
    QList<QTouchEvent::TouchPoint> listTouchPoints;
    QTouchEvent::TouchPoint cursor(tcur->getCursorID());
    QPoint p;

    p = QPoint(tcur->getX() * _screenWidth, tcur->getY() * _screenHeight);

    cursor.setScreenPos(p);
    cursor.setState(Qt::TouchPointPrimary); // must be set to trigger mouse events

    listTouchPoints.append( cursor );

    t = new QTouchEvent(QEvent::TouchBegin, QTouchEvent::TouchScreen, Qt::NoModifier,
        Qt::TouchPointPressed, listTouchPoints);



    QApplication::postEvent( this->target , t);
	*/
    //qDebug() << "add cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY();
}

void TUIOinterface::updateTuioCursor(TuioCursor *tcur)
{


    //qDebug() << "set cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY()
    //            << " " << tcur->getMotionSpeed() << " " << tcur->getMotionAccel() << " ";
}

void TUIOinterface::removeTuioCursor(TuioCursor *tcur)
{
	//std::cout << "del cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ")" << std::endl;
}

void TUIOinterface::refresh(TuioTime frameTime)
{
	this->getPoints();
	//std::cout << "refresh " << frameTime.getTotalMilliseconds() << std::endl;
    //qDebug() << "refresh";
}

void TUIOinterface::getPoints() {
	this->tuioList = _client->getTuioCursors();
	std::list<TuioCursor*>::iterator iterator;

	//std::cout << "list: " << this->tuioList.size() << std::endl;

	QTouchEvent *t;
	QList<QTouchEvent::TouchPoint> listTouchPoints;

	for ( iterator=this->tuioList.begin() ; iterator != this->tuioList.end(); iterator++ ) {

		QTouchEvent::TouchPoint cursor((*iterator)->getSessionID());
		QPoint p;
		p = QPoint((*iterator)->getX() * 640, (*iterator)->getY() * 480);

		cursor.setPos(p);
		p = QPoint((*iterator)->getX(), (*iterator)->getY());

		cursor.setScreenPos(p);



		cursor.setState(Qt::TouchPointMoved);

		listTouchPoints.append( cursor );
	}

	t = new QTouchEvent(QEvent::TouchBegin, QTouchEvent::TouchScreen, Qt::NoModifier,
	        Qt::TouchPointPressed, listTouchPoints);



	QApplication::postEvent( this->target , t);

	//std::cout << "id: " << (*iterator)->getSessionID() << " - x: " << (*iterator)->getX() << " - y: " << (*iterator)->getY() << std::endl;



	//QList<QTouchEvent::TouchPoint> touchPoints
	/* from /usr/include/qt4/QtGui/qevent.h
	 * // internal
        void setId(int id);
        void setState(Qt::TouchPointStates state);
        void setPos(const QPointF &pos);
        void setScenePos(const QPointF &scenePos);
        void setScreenPos(const QPointF &screenPos);
        void setNormalizedPos(const QPointF &normalizedPos);
        void setStartPos(const QPointF &startPos);
        void setStartScenePos(const QPointF &startScenePos);
        void setStartScreenPos(const QPointF &startScreenPos);
        void setStartNormalizedPos(const QPointF &startNormalizedPos);
        void setLastPos(const QPointF &lastPos);
        void setLastScenePos(const QPointF &lastScenePos);
        void setLastScreenPos(const QPointF &lastScreenPos);
        void setLastNormalizedPos(const QPointF &lastNormalizedPos);
        void setRect(const QRectF &rect);
        void setSceneRect(const QRectF &sceneRect);
        void setScreenRect(const QRectF &screenRect);
        void setPressure(qreal pressure);
        QTouchEvent::TouchPoint &operator=(const QTouchEvent::TouchPoint &other);
        */
}

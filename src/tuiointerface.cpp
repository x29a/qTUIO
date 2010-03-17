
#include "tuiointerface.h"


#include <QDebug>
#include <QTouchEvent>
#include <QApplication>
#include <QDesktopWidget>


TUIOinterface::TUIOinterface() :
    TuioListener()
{
	// stub
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

    qDebug() << "Touch started";

    qApp->postEvent( qApp->widgetAt(p) , t);
    //qDebug() << "add cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY();
}

void TUIOinterface::updateTuioCursor(TuioCursor *tcur)
{

    //qDebug() << "set cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY()
    //            << " " << tcur->getMotionSpeed() << " " << tcur->getMotionAccel() << " ";
}

void TUIOinterface::removeTuioCursor(TuioCursor *tcur)
{
	std::cout << "del cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ")" << std::endl;
}

void TUIOinterface::refresh(TuioTime frameTime)
{
	//std::cout << "refresh " << frameTime.getTotalMilliseconds() << std::endl;
    //qDebug() << "refresh";
}

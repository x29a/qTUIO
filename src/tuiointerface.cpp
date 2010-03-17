
#include "tuiointerface.h"


#include <QDebug>


TUIOinterface::TUIOinterface() :
    TuioListener()
{
	// stub
    int port = 3333;
    _client = new TuioClient(port);
    _client->addTuioListener(this);
}

TUIOinterface::~TUIOinterface()
{
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

void TUIOinterface::addTuioCursor(TuioCursor *tcur)
{
    qDebug() << "add cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY();
}

void TUIOinterface::updateTuioCursor(TuioCursor *tcur)
{
    qDebug() << "set cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY()
                << " " << tcur->getMotionSpeed() << " " << tcur->getMotionAccel() << " ";
}

void TUIOinterface::removeTuioCursor(TuioCursor *tcur)
{
	std::cout << "del cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ")" << std::endl;
}

void TUIOinterface::refresh(TuioTime frameTime)
{
	//std::cout << "refresh " << frameTime.getTotalMilliseconds() << std::endl;
    qDebug() << "refresh";
}

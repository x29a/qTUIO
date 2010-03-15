#include "tuiointerface.h"


TUIOinterface::TUIOinterface()
{
	// stub
}

TUIOinterface::~TUIOinterface()
{
	// stub
}

void TUIOinterface::start()
{
	int port = 3333;

	client = new TuioClient;
	client->addTuioListener(this);
	client->connect(true);
}

void TUIOinterface::addTuioObject(TuioObject *tobj) {
	std::cout << "add obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ") "<< tobj->getX() << " " << tobj->getY() << " " << tobj->getAngle() << std::endl;
}

void TUIOinterface::updateTuioObject(TuioObject *tobj) {
	std::cout << "set obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ") "<< tobj->getX() << " " << tobj->getY() << " " << tobj->getAngle()
				<< " " << tobj->getMotionSpeed() << " " << tobj->getRotationSpeed() << " " << tobj->getMotionAccel() << " " << tobj->getRotationAccel() << std::endl;
}

void TUIOinterface::removeTuioObject(TuioObject *tobj) {
	std::cout << "del obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ")" << std::endl;
}

void TUIOinterface::addTuioCursor(TuioCursor *tcur) {
	std::cout << "add cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY() << std::endl;
}

void TUIOinterface::updateTuioCursor(TuioCursor *tcur) {
	std::cout << "set cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY()
				<< " " << tcur->getMotionSpeed() << " " << tcur->getMotionAccel() << " " << std::endl;
}

void TUIOinterface::removeTuioCursor(TuioCursor *tcur) {
	std::cout << "del cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ")" << std::endl;
}

void TUIOinterface::refresh(TuioTime frameTime) {
	//std::cout << "refresh " << frameTime.getTotalMilliseconds() << std::endl;
}

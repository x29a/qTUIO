#ifndef TUIOINTERFACE_H
#define TUIOINTERFACE_H

#include <QEvent>
#include <QObject>
#include <QDebug>
#include <QTouchEvent>
#include <list>

#include "TuioListener.h"
#include "TuioClient.h"
#include "TuioObject.h"
#include "TuioCursor.h"
#include "TuioPoint.h"


using namespace TUIO;

class TUIOinterface : public TuioListener
{

public:
    TUIOinterface();
    ~TUIOinterface();

	void addTuioObject(TuioObject *tobj);
	void updateTuioObject(TuioObject *tobj);
	void removeTuioObject(TuioObject *tobj);

	void addTuioCursor(TuioCursor *tcur);
	void updateTuioCursor(TuioCursor *tcur);
	void removeTuioCursor(TuioCursor *tcur);

	void refresh(TuioTime frameTime);
	void getPoints(void);

	void start(void);

	void setTarget(QObject *target);

    TuioClient * _client;

private:
    int _screenHeight;
    int _screenWidth;
    QObject *target;

    std::list<TuioCursor*> tuioList;
};

#endif // TUIOINTERFACE_H

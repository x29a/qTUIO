#include "tuiothread.h"
#include "tuiointerface.h"
#include <QDebug>

TUIOThread::TUIOThread(QObject *parent) :
    QThread(parent)
{
    _tuioInterface = new TUIOinterface();
    qDebug() << "thread: " << parent;
    _tuioInterface->setTarget(parent);

}

TUIOThread::~TUIOThread()
{
    qDebug() << "Thread dead";
    delete _tuioInterface;
}


void TUIOThread::run()
{
    //qDebug() << (_tuioInterface->_client->isConnected() ? "Yes" : "No" );
    _tuioInterface->start();
    //qDebug() << (_tuioInterface->_client->isConnected() ? "Yes" : "No" );


    exec();
}

bool TUIOThread::event(QEvent *event){
	if(event->type() == QEvent::ToolTip) {
		qDebug() << "thread tooltip detected";
	}
	return true;
}

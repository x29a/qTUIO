#include "tuiothread.h"

tuioThread::tuioThread(QObject *parent) :
    QThread(parent)
{
	iface = new TUIOinterface()

}

tuioThread::~tuioThread()
{
	delete iface;
}


tuioThread::run()
{
	iface->start();
}

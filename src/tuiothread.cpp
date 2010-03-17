#include "tuiothread.h"
#include "tuiointerface.h"
#include <QDebug>

TUIOThread::TUIOThread(QObject *parent) :
    QThread(parent)
{
    _tuioInterface = new TUIOinterface();

}

TUIOThread::~TUIOThread()
{
    qDebug() << "Thread dead";
    delete _tuioInterface;
}


void TUIOThread::run()
{
    qDebug() << (_tuioInterface->_client->isConnected() ? "Yes" : "No" );
    _tuioInterface->start();
    qDebug() << (_tuioInterface->_client->isConnected() ? "Yes" : "No" );


    exec();
}

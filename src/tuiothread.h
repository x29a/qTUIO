#ifndef TUIOTHREAD_H
#define TUIOTHREAD_H

#include <QThread>

class
#include "tuiointerface.h"

class tuioThread : public QThread
{
Q_OBJECT
public:
    explicit tuioThread(QObject *parent = 0);
	~tuioThread();


	void run();

signals:

public slots:


private
	TUIOinterface *iface;

};

#endif // TUIOTHREAD_H

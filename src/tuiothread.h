#ifndef TUIOTHREAD_H
#define TUIOTHREAD_H

#include <QThread>

class TUIOinterface;

class TUIOThread : public QThread
{
    Q_OBJECT

public:
    explicit TUIOThread(QObject *parent = 0);
    ~TUIOThread();


	void run();

signals:

public slots:


private:
    TUIOinterface *_tuioInterface;

};

#endif // TUIOTHREAD_H

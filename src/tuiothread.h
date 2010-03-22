#ifndef TUIOTHREAD_H
#define TUIOTHREAD_H

#include <QThread>
#include <QEvent>

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
    bool event(QEvent *event);

};

#endif // TUIOTHREAD_H

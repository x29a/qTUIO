#include "qtuio.h"

#include <QtGui>
#include <QApplication>
#include "tuiointerface.h"

int main(int argc, char *argv[])
{
    /*QApplication a(argc, argv);
    qTUIO w;
    w.show();
    return a.exec();
    */
	TUIOinterface iface;
	iface.start();
}

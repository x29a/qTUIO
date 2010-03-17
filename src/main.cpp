#include <QtGui>
#include <QCoreApplication>
#include "tuiothread.h"
#include "tuiowidget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

    TUIOThread t;
	t.start();

    TUIOWidget w;
	w.show();

	return a.exec();
}

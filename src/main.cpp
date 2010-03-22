#include <QtGui>
#include <QCoreApplication>
#include "tuiothread.h"
#include "tuiowidget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	TUIOWidget w;

    TUIOThread t(&w);
	t.start();


	w.show();

	return a.exec();
}

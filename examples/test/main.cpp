#include <QApplication>

#include "test.h"
#include "qtuio.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	Test testWidget;
	//testWidget.show();

	QTuio qTUIO;
	qTUIO.run();
	return app.exec();
}

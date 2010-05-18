#include <QApplication>
#include <QGraphicsView>

#include "cross.h"
#include "qtuio.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QGraphicsScene scene;
    QGraphicsView view(&scene);
    view.setWindowTitle("qTUIO config");

    Cross *cross = new Cross();

    scene.addItem(cross);

    QTuio qTUIO(&view);
    qTUIO.run();

    view.showFullScreen();

    return app.exec();
}


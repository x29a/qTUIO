/*
	This file is part of an example for:

	qTUIO - TUIO Interface for Qt

	Example written by x29a <0.x29a.0@gmail.com>

	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QApplication>
#include <QGraphicsView>
//#include <QtOpenGL>

#include "pong.h"
#include "spectator.h"
#include "qtuio.h"

 int main(int argc, char **argv)
 {
     QApplication app(argc, argv);

     Pong scene(800,600);

     Spectator view(&scene);
     //view.setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));

     QTuio qTUIO(&view);
     qTUIO.run();

     view.setRenderHint(QPainter::Antialiasing);
     view.setCacheMode(QGraphicsView::CacheBackground);
     view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "qPONG"));
     view.fitInView(scene.sceneRect(), Qt::KeepAspectRatio);

     //view.showFullScreen();
     //view.show();
     view.showMaximized();
     return app.exec();
 }

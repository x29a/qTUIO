/****************************************************************************
 **
 ** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 ** All rights reserved.
 ** Contact: Nokia Corporation (qt-info@nokia.com)
 **
 ** This file is part of the examples of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:LGPL$
 ** Commercial Usage
 ** Licensees holding valid Qt Commercial licenses may use this file in
 ** accordance with the Qt Commercial License Agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and Nokia.
 **
 ** GNU Lesser General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU Lesser
 ** General Public License version 2.1 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.LGPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU Lesser General Public License version 2.1 requirements
 ** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 **
 ** In addition, as a special exception, Nokia gives you certain additional
 ** rights.  These rights are described in the Nokia Qt LGPL Exception
 ** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
 **
 ** GNU General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU
 ** General Public License version 3.0 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.GPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU General Public License version 3.0 requirements will be
 ** met: http://www.gnu.org/copyleft/gpl.html.
 **
 ** If you have questions regarding the use of this file, please contact
 ** Nokia at qt-info@nokia.com.
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

#include <QApplication>
#include <QGraphicsView>
#include <QDesktopWidget>

#include "knob.h"
#include "qtuio.h"

#include <QtDebug>

 int main(int argc, char **argv)
 {
     QApplication app(argc, argv);

     QGraphicsScene scene;
     QGraphicsView view(&scene);

     Knob *knob1 = new Knob;
     knob1->moveBy(-55, 0);
     Knob *knob2 = new Knob;
     knob2->moveBy(55, 0);

     scene.addItem(knob1);
     scene.addItem(knob2);

     QTuio qTUIO(&view);
     qTUIO.run();

     view.setRenderHint(QPainter::Antialiasing);
     view.setCacheMode(QGraphicsView::CacheBackground);
     //view.setGeometry(QRect(512, 100, 256, 100));
     view.showFullScreen();
     //view.scale(2.5, 2.5);
     //view.show();
     //view.showMaximized();
     scene.setSceneRect(view.rect().adjusted(-view.rect().width()/2, -view.rect().height()/2, -view.rect().width()/2, -view.rect().height()/2));
     //view.fitInView(scene.sceneRect(), Qt::KeepAspectRatio);


     return app.exec();
 }

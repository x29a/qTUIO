#include "tuiowidget.h"
#include "tuiobutton.h"
#include <QGridLayout>
#include <QList>
#include <QTouchEvent>

TUIOWidget::TUIOWidget()
{
    //setWindowState(Qt::WindowFullScreen);
	setAttribute(Qt::WA_AcceptTouchEvents);
	setAttribute(Qt::WA_StaticContents);

	myPenColors
	             << QColor("green")
	             << QColor("purple")
	             << QColor("red")
	             << QColor("blue")
	             << QColor("yellow")

	             << QColor("pink")
	             << QColor("orange")
	             << QColor("brown")
	             << QColor("grey")
	             << QColor("black");

	this->createImage();
	this->wHeight=480;
	this->wWidth=640;
}


bool TUIOWidget::createImage()
{
	QImage newImage(QSize(this->wWidth,this->wHeight), QImage::Format_RGB32);
	newImage.fill(qRgb(255, 255, 255));

    this->image = newImage;
    update();
    return true;
}


void TUIOWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    const QRect rect = event->rect();
    painter.drawImage(rect.topLeft(), image, rect);
}

void TUIOWidget::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        this->wHeight=newHeight;
        this->wWidth=newWidth;
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

int TUIOWidget::getHeight() {
	return this->wHeight;
}

int TUIOWidget::getWidth() {
	return this->wWidth;
}

void TUIOWidget::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}



bool TUIOWidget::event(QEvent *event){
	/* works
	if(event->type() == QEvent::TouchBegin) {
		qDebug() << "widget TouchBegin detected";
		QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
		foreach (const QTouchEvent::TouchPoint &touchPoint, touchPoints) {
			qDebug() << "pos" << touchPoint.screenPos();
		}
	}
	else
	{
		//qDebug() << "widget event detected";
	}
	//return false;
	return QWidget::event(event);
	*/
	switch (event->type()) {
	     case QEvent::TouchBegin:
	     case QEvent::TouchUpdate:
	     case QEvent::TouchEnd:
	     {
	         QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
	         foreach (const QTouchEvent::TouchPoint &touchPoint, touchPoints) {
	             switch (touchPoint.state()) {
					 case Qt::TouchPointStationary:
	                 // don't do anything if this touch point hasn't moved
	            	 qDebug() << "dont move";
	                 continue;
					 default:
	                 {
	                	 //qDebug() << "received: " << touchPoint.pos();
	                     QRectF rect = touchPoint.rect();
	                     if (rect.isEmpty()) {
	                         qreal diameter = qreal(50) * 0.2;
	                         rect.setSize(QSizeF(diameter, diameter));
	                     }

	                     QPainter painter(&image);
	                     painter.setPen(Qt::NoPen);
	                     painter.setBrush(myPenColors.at(touchPoint.id() % myPenColors.count()));
	                     painter.drawEllipse(rect);
	                     painter.end();

	                     int rad = 2;
	                     update(rect.toRect().adjusted(-rad,-rad, +rad, +rad));
	                 }
	                 break;
	             }
	         }
	         break;
	     }
	     default:
	         return QWidget::event(event);
	     }
	     return true;

}

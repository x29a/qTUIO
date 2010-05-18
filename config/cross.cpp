#include "cross.h"

#define DEBUG

#include <QBrush>
#include <QTouchEvent>

#include <QApplication>
#include <QDesktopWidget>
#include <QPen>
#include <QGraphicsWidget>
#include <QThread>

#include <QProcessEnvironment>
#include <QFile>
#include <QDomDocument>
#include <QTextStream>

#ifdef DEBUG
    #include <QtDebug>
#endif

#define MAXCOUNT 5


Cross::Cross()
    : QGraphicsRectItem(qApp->desktop()->rect().width()/2-1, qApp->desktop()->rect().height()/2-30, 2, 60)
{
    this->setAcceptTouchEvents(true);
    this->setPen(QPen(Qt::red));
    this->setBrush(Qt::red);

    this->offset.setX(0);
    this->offset.setY(0);

    this->lr = new QGraphicsRectItem(qApp->desktop()->rect().width()/2-30, qApp->desktop()->rect().height()/2-1, 60, 2, this);
    this->lr->setAcceptTouchEvents(true);
    this->lr->setPen(QPen(Qt::red));
    this->lr->setBrush(Qt::red);

    this->x = 0;
    this->y = 0;
    this->cnt = 0;
}

int Cross::processConfig()
{
    QString home = QProcessEnvironment::systemEnvironment().value("HOME");
    QFile file(home.append("/.qtuioconfig"));
    if (file.open(QIODevice::WriteOnly)) {
        QDomDocument doc("qTUIOconfig");
        QDomElement root = doc.createElement("CONFIG");
        root.setAttribute("CONFIGURED", "TRUE");
        doc.appendChild(root);
        QDomElement elem = doc.createElement("OFFSET");
        elem.setAttribute("X", this->offset.x());
        elem.setAttribute("Y", this->offset.y());
        root.appendChild(elem);
        QTextStream ts(&file);
        ts << doc.toString();
        file.close();
#ifdef DEBUG
        qDebug() << "Configuration file saved";
#endif
        return 0;
    }
    return -1;
}


bool Cross::sceneEvent(QEvent *event)
{
    switch (event->type()) {
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
    {

        QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);

        if (this->offset.x() == 0 && this->offset.y() == 0) {
            foreach(const QTouchEvent::TouchPoint &tp, touchEvent->touchPoints()) {
                if (tp.screenPos().x() != 0 && tp.screenPos().y() != 0) {
                    this->x += tp.screenPos().x();
                    this->y += tp.screenPos().y();
                    this->cnt++;
#ifdef DEBUG
                    qDebug() << "Received " << cnt << " touchpoints. " << MAXCOUNT-cnt << " more touchpoints needed";
#endif
                }
            }
            if (this->cnt >= MAXCOUNT) {
                this->x = (int)((qreal)this->x / (qreal)this->cnt);
                this->y = (int)((qreal)this->y / (qreal)this->cnt);

                this->offset.setX(this->x - qApp->desktop()->rect().width()/2);
                this->offset.setY(this->y - qApp->desktop()->rect().height()/2);
                this->setBrush(Qt::green);
                this->setPen(QPen(Qt::green));
                this->lr->setBrush(Qt::green);
                this->lr->setPen(QPen(Qt::green));
                this->setAcceptTouchEvents(false);
                this->lr->setAcceptTouchEvents(false);
#ifdef DEBUG
                qDebug() << "Offset = (" << this->offset.x() << ", " << this->offset.y() << ")";
#endif
                qApp->exit(this->processConfig());
            }
        }

        break;
    }

    default:
        return QGraphicsItem::sceneEvent(event);
    }

    return true;
}


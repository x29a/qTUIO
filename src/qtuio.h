#ifndef QTUIO_H
#define QTUIO_H

#include <QtGui/QWidget>
#include "ui_qtuio.h"

class qTUIO : public QWidget
{
    Q_OBJECT

public:
    qTUIO(QWidget *parent = 0);
    ~qTUIO();

private:
    Ui::qTUIOClass ui;
};

#endif // QTUIO_H

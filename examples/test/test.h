#ifndef TEST_H
#define TEST_H

#include <QtGui>
#include <QWidget>

class Test : public QWidget
{
	Q_OBJECT
public:
	Test();
	~Test();

private:
	bool event(QEvent *event);
};
#endif

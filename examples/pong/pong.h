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

#ifndef PONG_H
#define PONG_H

#include <QGraphicsScene>
#include <QGraphicsItem>

#include "player.h"
#include "ball.h"

#define BORDER 30

class Pong : public QGraphicsScene
{
Q_OBJECT
public:
	Pong(int width, int height);

	void toggle_gameState(void);

protected:

public slots:
	void update_scene(void);
private:
	Player *player1, *player2;
	Ball *ball;
	QGraphicsRectItem *border;
	QGraphicsSimpleTextItem *score1,*score2;
	QGraphicsLineItem *middleLine;
	QTimer *timer;
	int dx, dy;
	int speed;

	float fps;

	bool active_game;

	// needed for touchevents
	bool event(QEvent *event);
};

#endif

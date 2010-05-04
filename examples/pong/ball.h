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

#ifndef BALL_H
#define BALL_H

#include <QGraphicsItem>
#include <QGraphicsEllipseItem>

#define BALL_SIZE 30
#define BALL_START_SPEED 2

class Ball : public QGraphicsEllipseItem
{
public:
	Ball();

	void setDir(void);

	void setDX(int dx);
	int getDX(void);
	void setDY(int dy);
	int getDY(void);
	void accelerate(void);
	int getSpeed(void);
	void resetSpeed(void);
private:
	int speed;
	int dx, dy;
};

#endif // BALL_H

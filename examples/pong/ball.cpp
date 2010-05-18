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

#include "ball.h"
#include <QBrush>
#include <QTouchEvent>
#include <QTime>


Ball::Ball() : QGraphicsEllipseItem(0, 0, BALL_SIZE, BALL_SIZE)
{
	// needed for multitouch events
	setAcceptTouchEvents(true);

	// define color
	this->setBrush(QBrush(Qt::black));

	this->setDir();

	// set initial speed
	this->resetSpeed();
}

void Ball::setDir(void)
{
	// init random number generator
	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

	// calculate startdirection
	this->dx=((qrand()%2)*2-1);
	this->dy=((qrand()%2)*2-1);
}

void Ball::setDX(int dx)
{
	if(dx == -1 || dx == 1)
	{
		this->dx = dx;
	}
}

void Ball::setDY(int dy)
{
	if(dy == -1 || dy == 1)
	{
		this->dy = dy;
	}
}

int Ball::getDX(void)
{
	return this->dx;
}

int Ball::getDY(void)
{
	return this->dy;
}

void Ball::accelerate(void)
{
        this->speed += 0.5;
}

qreal Ball::getSpeed(void)
{
	return this->speed;
}

void Ball::resetSpeed(void)
{
	this->speed = BALL_START_SPEED;
}

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

#include "player.h"

#include <QBrush>
#include <QTouchEvent>
#include <QDebug>


Player::Player(int side) : QGraphicsRectItem(0, 0, PLAYER_SIZE, PLAYER_SIZE*4)
{
	setAcceptTouchEvents(true);
	this->score = 0;

	if(side==1)
	{
		setBrush(QBrush(Qt::red));
	}
	else
	{
		setBrush(QBrush(Qt::blue));
	}
}

int Player::getScore(void)
{
	return this->score;
}

void Player::setScore(int newScore)
{
	this->score = newScore;
}

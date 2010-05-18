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

#include <QtGui>
#include <QCursor>
#include <QString>
#include <QDebug>

#include "pong.h"

Pong::Pong(int width, int height)
{
	this->setSceneRect(0, 0, width, height);

	this->active_game = FALSE;

	this->fps = 40;

	this->player1 = new Player(1);
	this->player2 = new Player(2);
	this->border = new QGraphicsRectItem(0, 0, this->width(), this->height());
	this->border->setBrush(QBrush(Qt::white));

	this->ball = new Ball;

	this->score1 = new QGraphicsSimpleTextItem(QString::number(this->player1->getScore()));
	this->score1->setBrush(QBrush(Qt::black));
	this->score2 = new QGraphicsSimpleTextItem(QString::number(this->player2->getScore()));
	this->score2->setBrush(QBrush(Qt::black));

	this->middleLine = new QGraphicsLineItem(this->width()/2,0,this->width()/2,this->height());

	this->addItem(this->border);
	this->addItem(this->ball);
	this->addItem(this->player1);
	this->addItem(this->player2);
	this->addItem(this->score1);
	this->addItem(this->score2);
	this->addItem(this->middleLine);


        this->player1->setPos(BORDER, (this->height()/2-PLAYER_SIZE*2));
        this->player2->setPos(this->width()-BORDER-PLAYER_SIZE, (this->height()/2-PLAYER_SIZE*2));
	this->ball->setPos(this->width()/2-BALL_SIZE/2, this->height()/2);
	this->score1->setPos((this->width()/2)-2*BORDER,BORDER);
	this->score2->setPos((this->width()/2)+2*BORDER,BORDER);


	this->timer = new QTimer(this);
	connect(this->timer, SIGNAL(timeout()), this, SLOT(update_scene()));

}

void Pong::toggle_gameState(void)
{
	if(this->active_game)
	{
		this->active_game = FALSE;
		this->timer->stop();
	}
	else
	{
		this->active_game = TRUE;
		this->timer->start(1000/this->fps);
	}

}

void Pong::update_scene(void)
{
	// score
	if(this->ball->x() <= (BORDER-2))
	{
		this->player2->setScore(this->player2->getScore()+1);
		this->ball->setPos(this->width()/2-BALL_SIZE/2, this->height()/2);
		this->ball->setDir();
		this->ball->resetSpeed();
		this->score2->setText(QString::number(this->player2->getScore()));
		this->toggle_gameState();
	}
	else if(this->ball->x() > (this->width()-BORDER+2))
	{
		this->player1->setScore(this->player1->getScore()+1);
		this->ball->setPos(this->width()/2-BALL_SIZE/2, this->height()/2);
		this->ball->setDir();
		this->ball->resetSpeed();
		this->score1->setText(QString::number(this->player1->getScore()));
		this->toggle_gameState();
	}
	// normal game
	else
	{
		if(this->ball->collidesWithItem(this->player1) || this->ball->collidesWithItem(this->player2))
		{
			this->ball->accelerate();
			this->ball->setDX(-this->ball->getDX());
		}
		if (this->ball->y()<=0 || this->ball->y()>=this->height()-BORDER) {
			this->ball->setDY(-this->ball->getDY());
		}

		this->ball->moveBy(this->ball->getSpeed()*this->ball->getDX(), this->ball->getSpeed()*this->ball->getDY());
	}
}


bool Pong::event(QEvent *event)
{
	switch (event->type())
	{
	case QEvent::TouchBegin:
	case QEvent::TouchUpdate:
	case QEvent::TouchEnd:
	{
		// only one touchpoint per side is taken into account
		bool didPlayer1=false, didPlayer2=false;

		QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
		foreach (const QTouchEvent::TouchPoint &touchPoint, touchPoints)
		{
			int yPos = touchPoint.scenePos().y() - 2*PLAYER_SIZE;

			if(yPos > (this->height()-4*PLAYER_SIZE))
				yPos = (this->height()-4*PLAYER_SIZE);
			if(yPos < 0)
				yPos = 0;

			// player 1 (left)
			if((touchPoint.scenePos().x() > 0)
					&& (touchPoint.scenePos().x() <= (this->width()/3))
					&& !didPlayer1)
			{
				this->player1->setPos(BORDER,yPos);
				didPlayer1=true;
			}
			// pause (middle)
			else if(touchPoint.scenePos().x() >= (this->width()/3)
					&& (touchPoint.scenePos().x() <= ((this->width()*2)/3)))
			{
				if(!this->active_game)
				{
					this->active_game = TRUE;
					this->timer->start(1000/this->fps);
				}
			}
			// player 2 (right)
			else if((touchPoint.scenePos().x() >= ((this->width()*2)/3))
					&& !didPlayer2)
			{
				this->player2->setPos(this->width()-BORDER-PLAYER_SIZE, yPos);
				didPlayer2=true;
			}
		}
	}
	break;
	default:
		return QGraphicsScene::event(event);
	}
	return true;
}


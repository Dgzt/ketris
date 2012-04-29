/***************************************************************************************************
*****    This file is part of Ketris.                                                          *****
*****                                                                                          *****
*****    Copyright (C) 2012  Zsuro Tibor <zsurotibor@gmail.com>                                *****
*****                                                                                          *****
*****    This program is free software: you can redistribute it and/or modify it under the     *****
*****    terms of the GNU General Public License as published by the Free Software Foundation, *****
*****    either version 3 of the License, or (at your option) any later version.               *****
*****                                                                                          *****
*****    This program is distributed in the hope that it will be useful, but WITHOUT ANY       *****
*****    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A       *****
*****    PARTICULAR PURPOSE.  See the GNU General Public License for more details.             *****
*****                                                                                          *****
*****    You should have received a copy of the GNU General Public License along with this     *****
*****    program. If not, see <http://www.gnu.org/licenses/>.                                  *****
***************************************************************************************************/
#include <QtCore/QTimer>
#include <QtCore/QTime>
#include <QtGui/QKeyEvent>
#include "centraltable.h"
#include "shape.h"

const int BEGIN_TIMER_MSEC = 500; //500

const int FIRST_NEXT_LEVEL_SCORE = 30; //30

//Scores
const int SHAPE_IS_ARRIVED_SCORE = 1;
const int REMOVED_FULL_ROW_SCORE = 3;

CentralTable::CentralTable( QWidget* parent ): Table( Table::CentralTable, parent )
{
	gameIsRunning = false;
	score = 0;
	level = 0;
	nextLevelScore = 0;
	
	currentShape = 0;
	nextShape = 0;
	shapeTimer = 0;
	
	shapeElapsedTime = 0;
	currentTimerMsec = 0;
	
	shapePos = QPoint(CENTRAL_TABLE_COLUMN_COUNT/2,0);
	
	shapeTimerMsec = BEGIN_TIMER_MSEC;
	
	setFocusPolicy(Qt::StrongFocus);
}

CentralTable::~CentralTable()
{
	if( currentShape ) 
		delete currentShape;
	
	if( nextShape )
		delete nextShape;
	
	if( shapeTimer )
		delete shapeTimer;
	
	if( shapeElapsedTime )
		delete shapeElapsedTime;
}

bool CentralTable::isCorrectTheNewPosition()
{
	//Check, the current shape is moves out from the table
	for( int i = 0 ; i < currentShape->getSquaresSize() ; ++i ) {
		if( shapePos.x() + currentShape->getPoint(i).x() < 0 || shapePos.x() + currentShape->getPoint(i).x() >= CENTRAL_TABLE_COLUMN_COUNT ){
			return false;
		}
		if( shapePos.y() + currentShape->getPoint(i).y() < 0 || shapePos.y() + currentShape->getPoint(i).y() >= CENTRAL_TABLE_ROW_COUNT ){
			return false;
		}
	}
	
	//Check, the current shape is moves to the other (part of) shape
	for( int i = 0 ; i < currentShape->getSquaresSize() ; ++i ){
		if( getSquare( shapePos.y() + currentShape->getPoint(i).y(), shapePos.x() + currentShape->getPoint(i).x() ) != QColor( Qt::black ) ){
			return false;
		}
	}
	
	return true;
}

void CentralTable::setNewShape()
{
	delete currentShape;
	currentShape = nextShape;
	nextShape = new Shape;
	
	shapePos.setX( CENTRAL_TABLE_COLUMN_COUNT/2 );
	shapePos.setY( 0 );
	
	emit newNextShape( nextShape );
}

void CentralTable::addToScore( int number )
{
	score += level*number;
	emit newScore( score );
	
	if( score >= nextLevelScore ){
		level++;
		emit newLevel( level );
			
		nextLevelScore *= 2;
			
		shapeTimerMsec *= 0.8;
	}
}

void CentralTable::removeFullRows()
{
	//Search full row
	bool fullRow;
	for( int row = CENTRAL_TABLE_ROW_COUNT -1 ; row >= 0 ; --row ){
		fullRow = true;
		for( int column = 0 ; column < CENTRAL_TABLE_COLUMN_COUNT ; ++column ){
			if( getSquare( row, column ) == QColor( Qt::black ) )
				fullRow = false;
		}
		
		if( fullRow ){
			//Copy the row to under row
			for( int copyRow = row ; copyRow >= 1 ; --copyRow ){
				for( int copyColumn = 0 ; copyColumn < CENTRAL_TABLE_COLUMN_COUNT ; ++copyColumn ){
					setSquare( copyRow, copyColumn, getSquare( copyRow-1, copyColumn ) );
				}
			}
			//The 0th row remove
			for( int column = 0 ; column < CENTRAL_TABLE_COLUMN_COUNT ; ++column ){
				setSquare( 0, column, QColor( Qt::black ) );
			}
			
			emit removedLine();
			
			//Add the score
			addToScore( REMOVED_FULL_ROW_SCORE );
			
			//Check again the row
			row++;
		}	
	}
}

void CentralTable::shapeTimerTimeoutSlot()
{
	//Delete the shape from the table
	delShape( shapePos, currentShape );
	//Set the new position, decrease the vertical position
	shapePos.ry()++;
	
	//Check the new position
	if( !isCorrectTheNewPosition() ){
		//Set the current shape position to the previous position
		shapePos.ry()--;
		
		addShape( shapePos, currentShape );
		
		//Add the score
		addToScore( SHAPE_IS_ARRIVED_SCORE );
		
		//Remove the rows what full
		removeFullRows();
		
		//Fixed the current shape, and set the new next shape
		setNewShape();
		
		//If the new shape position is incorrect, then game end
		if( !isCorrectTheNewPosition() ){
			emit gameEnd();
			gameIsRunning = false;
			return;
		}
	}
	
	//Put the shape to the table
	addShape( shapePos, currentShape );
	
	//Refresh the widget
	update();
	
	//Set the timer 
	currentTimerMsec = shapeTimerMsec;
	shapeTimer->start( currentTimerMsec );
	shapeElapsedTime->restart();
}

void CentralTable::startGame()
{
	//Set the current and next shape
	currentShape = new Shape;
	shapePos = QPoint( CENTRAL_TABLE_COLUMN_COUNT/2, 0 );
	addShape( shapePos, currentShape );
	
	nextShape = new Shape;
	emit newNextShape( nextShape );
	
	//Set the timer of current shape
	shapeTimer = new QTimer( this );
	connect( shapeTimer, SIGNAL( timeout() ), this, SLOT( shapeTimerTimeoutSlot() ) );
	shapeTimer->setSingleShot( true );
	
	shapeElapsedTime = new QTime;
	
	shapeTimerMsec = BEGIN_TIMER_MSEC;
	
	score = 0;
	emit newScore( score );
	
	level = 1;
	emit newLevel( level );
	nextLevelScore = FIRST_NEXT_LEVEL_SCORE;
	
	currentTimerMsec = shapeTimerMsec;
	shapeElapsedTime->start();
	shapeTimer->start( currentTimerMsec );

	gameIsRunning = true;
	update();
}

void CentralTable::closeGame()
{
	gameIsRunning = false;
	
	score = 0;
	emit newScore( score );
	
	level = 0;
	emit newLevel( level );
	nextLevelScore = 0;
	
	if( currentShape ){
		delete currentShape;
		currentShape = 0;
	}
	if( nextShape ){
		delete nextShape;
		nextShape = 0;
	}
	if( shapeTimer ){
		delete shapeTimer;
		shapeTimer = 0;
	}
	if( shapeElapsedTime ){
		delete shapeElapsedTime;
		shapeElapsedTime = 0;
	}
	
	clearTable();
	
	update();
}

void CentralTable::keyPressEvent(QKeyEvent* ke)
{
	//If the game is not running, not control the key press event
	if( !gameIsRunning ) 
		return;
	
	//Stop the timer, becouse do not step the shape, when controll the new position
	shapeTimer->stop();
	
	if( ke->key() == Qt::Key_Up ){
		//Rotate right
		
		delShape( shapePos, currentShape );
		currentShape->rotateRight();
		if( !isCorrectTheNewPosition() ){
			currentShape->rotateLeft();
		}
		addShape( shapePos, currentShape );
		
	}else if( ke->key() == Qt::Key_X ){
		//Rotate left
		
		delShape( shapePos, currentShape );
		currentShape->rotateLeft();
		if( !isCorrectTheNewPosition() ){
			currentShape->rotateRight();
		}
		addShape( shapePos, currentShape );
	
	}else if( ke->key() == Qt::Key_Down ){
		//Move down
		
		delShape( shapePos, currentShape );
		shapePos.ry()++;
		if( !isCorrectTheNewPosition() ){
			shapePos.ry()--;
		}
		addShape( shapePos, currentShape );
		
	} else if (ke->key() == Qt::Key_Left) {
		//Move left
		
		delShape( shapePos, currentShape );
		shapePos.rx()--;
		if( !isCorrectTheNewPosition() ){
			shapePos.rx()++;
		}
		addShape( shapePos, currentShape );
		
	} else if (ke->key() == Qt::Key_Right) {
		//Move right
		
		delShape( shapePos, currentShape );
		shapePos.rx()++;
		if( !isCorrectTheNewPosition() ){
			shapePos.rx()--;
		}
		addShape( shapePos, currentShape );
	}
	
	//Continue the time, where was it paused
	int newTimerTime = currentTimerMsec - shapeElapsedTime->elapsed();;
	if( newTimerTime < 0 ) newTimerTime  = shapeTimerMsec;
	
	currentTimerMsec = newTimerTime;
	
	shapeElapsedTime->restart();
	shapeTimer->start( currentTimerMsec );
	
	update();
}

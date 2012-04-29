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
#ifndef board_h
#define board_h

#include "table.h"

class Shape;
class QKeyEvent;
class QTimer;
class QTime;

class CentralTable : public Table 
{
	Q_OBJECT
	
	Shape* currentShape;
	Shape* nextShape;
	
	QTimer* shapeTimer;
	QTime* shapeElapsedTime;
	int shapeElapsedMsec;
	
	/* The score system:
	 * -----------------
	 *  -Every deposited shapes are leve*1 score
	 *  -Every removed lines are level*3 score
	 */
	int score;
	
	//This is the number of level
	int level;
	//What score, when grow the level
	int nextLevelScore;
	
	//The shape position on the table
	QPoint shapePos;
	
	//If the game is running, this is true, else fals
	//bool gameIsRunning;
	
	//This variable set the timer msec when start the timer
	int shapeTimerMsec;
	//This variable set the timer msec when pressed key and set the part of shapeTimerMsec
	int currentTimerMsec;
	
	//Start or resume the shape timer
	void startShapeTimer();
	//Stop or pause the shape timer
	void stopShapeTimer();
	
	//If the position is correct, return true, else false
	bool isCorrectTheNewPosition();
	//This function fixed the shape, and set the new shape
	void setNewShape();
	
	//add the number to score
	void addToScore( int );
	
	//Remove the full rows
	void removeFullRows();
	
private slots:
	void shapeTimerTimeoutSlot();
	
public:
    CentralTable( QWidget* parent = 0 );
    ~CentralTable();
	
	void startGame();
	void closeGame();
	void pauseGame( bool );
	
public slots:
	void moveLeftSlot();
	void moveRightSlot();
	void moveDownSlot();
	void fastMoveDownSlot();
	void rotateLeftSlot();
	void rotateRightSlot();
	
//protected:
//	void keyPressEvent( QKeyEvent * );
	
signals:
	void newNextShape( Shape* );
	void newScore( int );
	void newLevel( int );
	void gameEnd();
	
	void removedLine();
	
};

#endif //board_h



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
#ifndef table_h
#define table_h

#include <QtGui/QWidget>

const int CENTRAL_TABLE_ROW_COUNT = 20;
const int CENTRAL_TABLE_COLUMN_COUNT = 10;

const int NEXT_SHAPE_TABLE_ROW_COUNT = 4;
const int NEXT_SHAPE_TABLE_COLUMN_COUNT = NEXT_SHAPE_TABLE_ROW_COUNT;

const int SQUARE_FRAME = 1;

class QResizeEvent;
class QPaintEvent;
class Shape;

class Table : public QWidget
{	
	//Q_OBJECT
protected:
	enum TableType{ CentralTable, NextShapeTable };
	
	void setSquare( int, int, QColor );
	QColor getSquare( int, int );
	
	void clearTable();
	
	void addShape( QPoint, Shape* );
	void delShape( QPoint, Shape* );
	
	void paintEvent( QPaintEvent* );
	
private:
	TableType tableType;
	
	QColor **table;
	
	int tableRowSize;
	int tableColumnSize;
	
	int squareSize;
	
public:
	Table( TableType, QWidget *parent = 0 );
	virtual ~Table();
	
	//The main window set the square size
	void setSquareSize( int );
	
};

#endif //table_h

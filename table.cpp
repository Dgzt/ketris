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
#include <QtGui/QColor>
#include <QtGui/QResizeEvent>
#include <QtGui/QPaintEvent>
#include <QtGui/QPainter>
#include "shape.h"
#include "table.h"

Table::Table( TableType type, QWidget* parent ): QWidget( parent )
{
	squareSize = 0;
	tableType = type;
	
	if (tableType == Table::CentralTable) {
		tableRowSize = CENTRAL_TABLE_ROW_COUNT;
		tableColumnSize = CENTRAL_TABLE_COLUMN_COUNT;
	} else { //Table::NextShapeTable
		tableRowSize = NEXT_SHAPE_TABLE_ROW_COUNT;
		tableColumnSize = NEXT_SHAPE_TABLE_COLUMN_COUNT;
	}
	
	table = new QColor*[tableRowSize];
	for (int row = 0 ; row < tableRowSize ; ++row) {
		table[row] = new QColor[tableColumnSize];
	}
	
	clearTable();
}

Table::~Table()
{
	for (int row = 0 ; row < tableRowSize ; ++row) {
		delete[] table[row];
	}
	delete[] table;
}

void Table::setSquare( int row, int column, QColor color )
{
	table[row][column] = color;
}

QColor Table::getSquare( int row, int column )
{
	return table[row][column];
}

void Table::addShape( QPoint pos, Shape* shape )
{
	for (int i = 0 ; i < shape->getSquaresSize() ; ++i) {
		table[ pos.y() + shape->getPoint(i).y() ][ pos.x() + shape->getPoint(i).x() ] = shape->getColor();
	}
}

void Table::delShape( QPoint pos, Shape* shape )
{
	for (int i = 0 ; i < shape->getSquaresSize() ; ++i) {
		table[ pos.y() + shape->getPoint(i).y() ][ pos.x() + shape->getPoint(i).x() ] = QColor( Qt::black );
	}
}

void Table::paintEvent( QPaintEvent* pe )
{
    QWidget::paintEvent(pe);
	
	QPainter painter( this );
	painter.fillRect( 0, 0, width(), height(), Qt::black );
	
	/*for (int row = 0 ; row < tableRowSize ; ++row) {
		for (int column = 0 ; column < tableColumnSize ; ++column) {
			painter.fillRect( column*squareSize, 
							  row*squareSize, 
							  squareSize-1, 
							  squareSize-1, 
							  //table[row][column]
							  QColor(Qt::cyan)
							);
		}
	}*/
	
	for (int row = 0 ; row < tableRowSize ; ++row) {
		for (int column = 0 ; column < tableColumnSize ; ++column) {
			painter.fillRect( column*squareSize + (column+1)*SQUARE_FRAME, 
							  row*squareSize + (row+1)*SQUARE_FRAME, 
							  squareSize, 
							  squareSize, 
							  table[row][column]
							  //QColor(Qt::cyan)
							);
		}
	}
	
	painter.end();
}

void Table::setSquareSize( int size )
{
	squareSize = size;
}

void Table::clearTable()
{
	for (int row = 0 ; row < tableRowSize ; ++row) {
		for (int column = 0 ; column < tableColumnSize ; ++column) {
			table[row][column] = QColor(Qt::black);
		}
	}
}


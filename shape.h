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
#ifndef shape_h
#define shape_h

#include <QtCore/QPoint>
#include <QtGui/QColor>

class Shape
{
	enum ShapeType{ J, O, L, I, S, Z, T };
	
	static const int SQUARE_SIZE = 4;
	
	ShapeType type;

	/*	The all shape are 4 square.
	 *	The tilePos the change to the shape's central position.
	 */	
	QPoint tilePos[SQUARE_SIZE];
	//QPoint* tilePos;
	
	QColor color;
	
	//Form between 0 and 3 (and equal), this variable set the shape rotate
	int form;
	//
	
	void setForm( int );

public:
	Shape();
	//Shape( Shape* );
	
	int getSquaresSize();
	QPoint getPoint( int );
	QColor getColor();
	
	void rotateLeft();
	void rotateRight();
	
};

#endif //shape_h

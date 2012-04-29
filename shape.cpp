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
#include "shape.h"

const int SHAPE_TYPE_SIZE = 7; //J,O,L,I,S,Z,T

//J
const QPoint formJ[4][4] = {  { QPoint(-1, 0), QPoint( 0, 0), QPoint( 1, 0), QPoint( 1, 1) }, 
							  { QPoint( 0,-1), QPoint( 0, 0), QPoint(-1, 1), QPoint( 0, 1) },
							  { QPoint(-1,-1), QPoint(-1, 0), QPoint( 0, 0), QPoint( 1, 0) },
							  { QPoint( 0,-1), QPoint( 1,-1), QPoint( 0, 0), QPoint( 0, 1) } };
//O
const QPoint formO[4][4] = { { QPoint(-1, 0), QPoint( 0, 0), QPoint(-1, 1), QPoint( 0, 1) },
							 { QPoint(-1, 0), QPoint( 0, 0), QPoint(-1, 1), QPoint( 0, 1) },
							 { QPoint(-1, 0), QPoint( 0, 0), QPoint(-1, 1), QPoint( 0, 1) },
							 { QPoint(-1, 0), QPoint( 0, 0), QPoint(-1, 1), QPoint( 0, 1) } };
//L
const QPoint formL[4][4] = { { QPoint(-1, 0), QPoint( 0, 0), QPoint( 1, 0), QPoint(-1, 1) },
							 { QPoint(-1,-1), QPoint( 0,-1), QPoint( 0, 0), QPoint( 0, 1) },
							 { QPoint(-1, 0), QPoint( 0, 0), QPoint( 1, 0), QPoint( 1,-1) },
							 { QPoint( 0,-1), QPoint( 0, 0), QPoint( 0, 1), QPoint( 1, 1) } };
//I
const QPoint formI[4][4] = { { QPoint(-2, 0), QPoint(-1, 0), QPoint( 0, 0), QPoint( 1, 0) },
							 { QPoint(-1,-1), QPoint(-1, 0), QPoint(-1, 1), QPoint(-1, 2) },
							 { QPoint(-2, 0), QPoint(-1, 0), QPoint( 0, 0), QPoint( 1, 0) },
							 { QPoint(-1,-1), QPoint(-1, 0), QPoint(-1, 1), QPoint(-1, 2) } };
//S
const QPoint formS[4][4] = { { QPoint( 0, 0), QPoint( 1, 0), QPoint(-1, 1), QPoint( 0, 1) },
							 { QPoint( 0,-1), QPoint( 0, 0), QPoint( 1, 0), QPoint( 1, 1) },
							 { QPoint( 0, 0), QPoint( 1, 0), QPoint(-1, 1), QPoint( 0, 1) },
							 { QPoint( 0,-1), QPoint( 0, 0), QPoint( 1, 0), QPoint( 1, 1) } };
//Z
const QPoint formZ[4][4] = { { QPoint(-1, 0), QPoint( 0, 0), QPoint( 0, 1), QPoint( 1, 1) },
							 { QPoint( 1, 0), QPoint( 0, 1), QPoint( 1, 1), QPoint( 0, 2) },
							 { QPoint(-1, 0), QPoint( 0, 0), QPoint( 0, 1), QPoint( 1, 1) },
							 { QPoint( 1, 0), QPoint( 0, 1), QPoint( 1, 1), QPoint( 0, 2) } };

//T
const QPoint formT[4][4] = { { QPoint(-1, 0), QPoint( 0, 0), QPoint( 1, 0), QPoint( 0, 1) },
							 { QPoint( 0,-1), QPoint(-1, 0), QPoint( 0, 0), QPoint( 0, 1) },
							 { QPoint( 0,-1), QPoint(-1, 0), QPoint( 0, 0), QPoint( 1, 0) },
							 { QPoint( 0,-1), QPoint( 0, 0), QPoint( 1, 0), QPoint( 0, 1) } };

Shape::Shape()
{
	int random = qrand()%SHAPE_TYPE_SIZE;
	
	//
	//random = 6;
	//
	
	form = 0;
	
	//Setup the shapes standard positions
	switch (random) {
		case 0 : //J
				type = J;
				color = QColor( Qt::lightGray );
				
				//tilePos = shapeJ[4];
				setForm( form );
				
				break;
		case 1 : //O
				type = O;
				color = QColor( Qt::blue );
				
				setForm( form );
				
				break;
		case 2 : //L
				type = L;
				color = QColor( "#7D26CD" ); //Purple
				
				setForm( form );
				
				break;
		case 3 : //I
				type = I;
				color = QColor( Qt::red );
				
				setForm( form );
				
				break;
		case 4 : //S
				type = S;
				color = QColor( Qt::green );
				
				setForm( form );
				
				break;
		case 5 : //Z
				type = Z;
				color = QColor( Qt::cyan );
				
				setForm( form );
				
				break;
		case 6 : //T
				type = T;
				color = QColor( "#964514" ); //Orange-brown
				
				setForm( form );
				
				break;
	}
}

void Shape::setForm( int copyRow )
{
	for( int i = 0 ; i < SQUARE_SIZE ; ++i ){
		switch (type) {
			case J : tilePos[i] = formJ[copyRow][i]; break;
			case O : tilePos[i] = formO[copyRow][i]; break;
			case L : tilePos[i] = formL[copyRow][i]; break;
			case I : tilePos[i] = formI[copyRow][i]; break;
			case S : tilePos[i] = formS[copyRow][i]; break;
			case Z : tilePos[i] = formZ[copyRow][i]; break;
			case T : tilePos[i] = formT[copyRow][i]; break;
		}
	}
}

int Shape::getSquaresSize()
{
	return SQUARE_SIZE;
}

QPoint Shape::getPoint(int pos)
{
	return tilePos[pos];
}

QColor Shape::getColor()
{
	return color;
}

void Shape::rotateLeft()
{
	if( form == 0 )
		form = 3;
	else
		form--;
		
	setForm( form );
}

void Shape::rotateRight()
{
	if( form == 3 ) 
		form = 0;
	else
		form++;
		
	setForm( form );
}


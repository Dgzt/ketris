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
#include "nextshapetable.h"
#include "shape.h"

NextShapeTable::NextShapeTable( QWidget* parent ): Table( Table::NextShapeTable, parent )
{
	nextShapePos = QPoint( NEXT_SHAPE_TABLE_COLUMN_COUNT/2, NEXT_SHAPE_TABLE_ROW_COUNT/2-1 );
}

void NextShapeTable::gameWasClosed()
{
	clearTable();
	update();
}

void NextShapeTable::setNewShapeSlot( Shape* nextShape )
{
	//Remove the previous shape
	clearTable();
	
	addShape( nextShapePos, nextShape );
	update();
}

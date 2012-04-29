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
#ifndef nextshapetable_h
#define nextshapetable_h

#include "table.h"

class Shape;

class NextShapeTable : public Table 
{
	Q_OBJECT
	
	QPoint nextShapePos;
	
public:
    NextShapeTable( QWidget* parent = 0 );
	
	void gameWasClosed();
	
public slots:
	void setNewShapeSlot( Shape* );

};

#endif //nextshapetable_h

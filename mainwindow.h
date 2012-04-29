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
#ifndef mainwindow_h
#define mainwindow_h

#include <KDE/KXmlGuiWindow>

class CentralTable;
class NextShapeTable;
class QResizeEvent;
class QLCDNumber;
class QLabel;
class KAction;

class MainWindow : public KXmlGuiWindow
{
    Q_OBJECT
  
	KAction* closeGameAction;
  
	//Central table
    CentralTable* centralTable;
	
	//Next shape
	QLabel* nextShapeLabel;
	NextShapeTable* nextShapeTable;
	
	//Score
	QLabel* scoreNumberLabel;
	QLCDNumber* scoreNumber;
	
	//Removed lines
	QLabel* removedLinesLabel;
	QLCDNumber* removedLinesNumber;
	
	//Level
	QLabel* levelLabel;
	QLCDNumber* levelNumber;
	
    void createActions();

	int getStringWidth( QString );
	int getStringHeight();

private slots:
    void gameNewSlot();
	void playerClosedGameSlot();
    void showHighscoresSlot();
	
	void removedLineSlot();
	void newScoreSlot( int );
	void newLevelSlot( int );
	void gameEndSlot();
  
public:
    MainWindow( QWidget* parent=0 );
    ~MainWindow();
    
protected:
	void resizeEvent( QResizeEvent * );

};

#endif // mainwindow_h

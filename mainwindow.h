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
class KToggleAction;

class MainWindow : public KXmlGuiWindow
{
    Q_OBJECT
  
	//
	bool windowResized;
	bool statusBarVisible;
	//
  
	//Move actions
	KAction* moveLeftAction;
	KAction* moveRightAction;
	KAction* moveDownAction;
	KAction* fastMoveDownAction;
	KAction* rotateLeftAction;
	KAction* rotateRightAction;
  
	//The player close the current game action
	KAction* closeGameAction;
	//Pause action
	KToggleAction* pauseAction;
	
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
	
	//Set the geometry the main window's widgets
	void resizeWidgets();

	void setEnabledMoveActions( bool );
	
	int getStringWidth( QString );
	int getStringHeight();

private slots:
    void gameNewSlot();
	void playerClosedGameSlot();
    void showHighscoresSlot();
	void pauseSlot();
	
	void removedLineSlot();
	void newScoreSlot( int );
	void newLevelSlot( int );
	void gameEndSlot();
  
public:
    MainWindow( QWidget* parent=0 );
    ~MainWindow();
    
protected:
	void resizeEvent( QResizeEvent* );
	
	//
	void paintEvent( QPaintEvent* );
	//

};

#endif // mainwindow_h

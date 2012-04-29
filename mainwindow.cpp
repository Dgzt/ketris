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
#include <QtCore/QTime>
#include <QtGui/QResizeEvent>
#include <QtGui/QLabel>
#include <QtGui/QLCDNumber>
#include <KDE/KApplication>
#include <KDE/KAction>
#include <KDE/KActionCollection>
#include <KDE/KStandardGameAction>
#include <KDE/KLocalizedString>
#include <KDE/KMenuBar>
#include <KDE/KStatusBar>
#include <KDE/KScoreDialog>
#include "mainwindow.h"
#include "centraltable.h"
#include "nextshapetable.h"

//
#include <iostream>
using namespace std;
//

//Main window constants
const int MAIN_WINDOW_MINIMUM_WIDTH = 400;
const int MAIN_WINDOW_MINIMUM_HEIGHT = 350;

const int MAIN_WINDOW_DEFAULT_WIDTH = 600;
const int MAIN_WINDOW_DEFAULT_HEIGHT = 600;

//Score number constants
const int SCORE_NUMBER_WIDTH = 100;
const int SCORE_NUMBER_HEIGTH = 60;

//Removed lines constants
const int REMOVED_LINES_WIDTH = 100;
const int REMOVED_LINES_HEIGHT = 60;

//Level constants
const int LEVEL_NUMBER_WIDTH = 100;
const int LEVEL_NUMBER_HEIGHT = 60;

//Next shape table constant
const int NEXT_SHAPE_TABLE_SIZE = 100+(NEXT_SHAPE_TABLE_ROW_COUNT+1)*SQUARE_FRAME; //This is not so good...
const int NEXT_SHAPE_SQUARE_SIZE = 25; 

//Widget distance constant
const int WIDGET_DISTANCE = 10;

MainWindow::MainWindow(QWidget *parent):KXmlGuiWindow(parent)
{  
	//To the random number generator
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
	
	//ScoreNumber
	scoreNumberLabel = new QLabel( i18n( "Scores:" ), this );
	scoreNumber = new QLCDNumber( this );
	
	//Removed lines
	removedLinesLabel = new QLabel( i18n( "Removed lines:" ), this );
	removedLinesNumber = new QLCDNumber( this );
	
	//Level
	levelLabel = new QLabel( i18n( "Level:" ), this );
	levelNumber = new QLCDNumber( this );
	
	//CentralTable
	centralTable = new CentralTable(this);
	
	//NextShape
	nextShapeLabel = new QLabel( i18n( "Next shape:" ), this );
	nextShapeTable = new NextShapeTable( this );

	//Set connects
	connect( centralTable, SIGNAL( newNextShape( Shape* ) ), nextShapeTable, SLOT( setNewShapeSlot( Shape* ) ) );
	connect( centralTable, SIGNAL( removedLine() ), this, SLOT( removedLineSlot() ));
	connect( centralTable, SIGNAL( newScore( int ) ), this, SLOT( newScoreSlot( int ) ) );
	connect( centralTable, SIGNAL( newLevel( int ) ), this, SLOT( newLevelSlot( int ) ) );
	connect( centralTable, SIGNAL( gameEnd() ), this, SLOT( gameEndSlot() ) );
	
    createActions();
	
	setMinimumWidth( MAIN_WINDOW_MINIMUM_WIDTH );
	setMinimumHeight( MAIN_WINDOW_MINIMUM_HEIGHT );
	
	statusBar()->showMessage( i18n( "Welcome to Ketris!" ) );
	
    //setupGUI();
	
	setupGUI( QSize( MAIN_WINDOW_DEFAULT_WIDTH, MAIN_WINDOW_DEFAULT_HEIGHT ) );
}

MainWindow::~MainWindow()
{
	delete scoreNumberLabel;
	delete scoreNumber;
	delete removedLinesLabel;
	delete removedLinesNumber;
	delete levelLabel;
	delete levelNumber;
	delete centralTable;
	delete nextShapeLabel;
	delete nextShapeTable;
}

//Create the actions of main window
void MainWindow::createActions()
{    
    //Game
    KStandardGameAction::gameNew(this,SLOT(gameNewSlot()),actionCollection());
	KStandardGameAction::highscores(this,SLOT(showHighscoresSlot()),actionCollection());
	closeGameAction = KStandardGameAction::end(this,SLOT(playerClosedGameSlot()),actionCollection());
	closeGameAction->setEnabled(false);
    KStandardGameAction::quit(this,SLOT(close()),actionCollection());
	
	//Settings
	//KStandardAction::preferences(this,SLOT(settingsSlot()),actionCollection());
}

int MainWindow::getStringWidth( QString text )
{
	return QFontMetrics( font() ).width( text );
}

int MainWindow::getStringHeight(/* QString text */)
{
	return QFontMetrics( font() ).height();
}

//Starting new game
void MainWindow::gameNewSlot()
{
    centralTable->startGame();
	
	closeGameAction->setEnabled(true);
}

//The player clicked to the "Game end" button
void MainWindow::playerClosedGameSlot()
{
	centralTable->closeGame();
	nextShapeTable->gameWasClosed();
	
	removedLinesNumber->display( 0 );
	closeGameAction->setEnabled(false);
}


//Show the highscores
void MainWindow::showHighscoresSlot()
{
	KScoreDialog ksdialog( KScoreDialog::Name, this );
	ksdialog.exec();
}

//Grow the number with 1
void MainWindow::removedLineSlot()
{
	removedLinesNumber->display( removedLinesNumber->intValue()+1 );
}

void MainWindow::newScoreSlot( int score )
{
	scoreNumber->display( score );
}

void MainWindow::newLevelSlot( int level )
{
	levelNumber->display( level );
}

void MainWindow::gameEndSlot()
{	
	KScoreDialog ksdialog( KScoreDialog::Name, this );
	
	ksdialog.addScore( scoreNumber->value() );
	
	ksdialog.exec();
	
	centralTable->closeGame();
	nextShapeTable->gameWasClosed();
	
	removedLinesNumber->display( 0 );
	
	closeGameAction->setEnabled( false );
}

void MainWindow::resizeEvent( QResizeEvent *re )
{
    //QWidget::resizeEvent(re);
    Q_UNUSED(re);
	
	int menuBarHeigth = menuBar()->height();
	int statusBarHeight = statusBar()->height();
	
	int squareFrameNumOnRow = CENTRAL_TABLE_ROW_COUNT+1;
	int squareFrameNumOnColumn = CENTRAL_TABLE_COLUMN_COUNT+1;
	
	//
	//CentralTable
	//
	
	//The maximum size (width, height) what the central table can use
	//4 widget distance before 3 widget on horizontal, and between 4 free space
	int maxWidthForCentralTable = width() - SCORE_NUMBER_WIDTH - NEXT_SHAPE_TABLE_SIZE - 4*WIDGET_DISTANCE;
	int maxHeightForCentralTable = height()-menuBarHeigth-statusBarHeight;
	
	double rate = (double)(CENTRAL_TABLE_COLUMN_COUNT+squareFrameNumOnColumn)/(CENTRAL_TABLE_ROW_COUNT+squareFrameNumOnRow);
	
	int newWidth, newHeight;
	
	if( maxHeightForCentralTable*rate <= maxWidthForCentralTable ){
        newWidth = maxHeightForCentralTable*rate;
		newHeight = maxHeightForCentralTable;
    }else{
        rate = (double)CENTRAL_TABLE_ROW_COUNT/CENTRAL_TABLE_COLUMN_COUNT;
	
        newWidth = maxWidthForCentralTable;
		newHeight = maxWidthForCentralTable*rate;
    }
    
    //Remove the excess pixels
    int centralTableSquareSize = (newHeight-squareFrameNumOnRow*SQUARE_FRAME)/CENTRAL_TABLE_ROW_COUNT;
	centralTable->setSquareSize( centralTableSquareSize );
	
	newWidth = centralTableSquareSize*CENTRAL_TABLE_COLUMN_COUNT + (CENTRAL_TABLE_COLUMN_COUNT+1)*SQUARE_FRAME;
	newHeight = centralTableSquareSize*CENTRAL_TABLE_ROW_COUNT + (CENTRAL_TABLE_ROW_COUNT+1)*SQUARE_FRAME;
    
    //Central table position on x coordinate
    int centralTablePosOnX = (width()-newWidth)/2;
    
	centralTable->setGeometry( centralTablePosOnX, menuBarHeigth, newWidth, newHeight );
	
	//Position to the widgets
	QPoint pos;
	//Size to the widgets
	QSize size;
	
	//   --Left part--
	int leftFreeSpaceCenter = centralTablePosOnX / 2;
	
	
	//
	//ScoreNumberLabel
	//
	pos.setX( leftFreeSpaceCenter - getStringWidth( scoreNumberLabel->text() )/2 );
	pos.setY( menuBarHeigth );
	
	//scoreNumberLabel->move( pos );
	size.setWidth( getStringWidth( scoreNumberLabel->text() ) );
	size.setHeight( getStringHeight() );
	scoreNumberLabel->setGeometry( QRect( pos, size ) );
	
	//
	//ScoreNumber
	//
	pos.setX( leftFreeSpaceCenter - SCORE_NUMBER_WIDTH/2 );
	pos.setY( menuBarHeigth + getStringHeight() + WIDGET_DISTANCE );
	
	size.setWidth( SCORE_NUMBER_WIDTH );
	size.setHeight( SCORE_NUMBER_HEIGTH );
	
	scoreNumber->setGeometry( QRect( pos, size ) );
	
	//
	//RemovedLineLabel
	//
	pos.setX( leftFreeSpaceCenter - getStringWidth( removedLinesLabel->text() )/2 );
	pos.setY( (height() - SCORE_NUMBER_HEIGTH)/2 - getStringHeight() - WIDGET_DISTANCE );
	
	//removedLinesLabel->move( pos );
	size.setWidth( getStringWidth( removedLinesLabel->text() ) );
	size.setHeight( getStringHeight() );
	removedLinesLabel->setGeometry( QRect( pos, size ) );
	
	//
	//RemovedLineNumber
	//
	pos.setX( leftFreeSpaceCenter - REMOVED_LINES_WIDTH/2 );
	pos.setY( (height() - REMOVED_LINES_HEIGHT)/2 );
	
	size.setWidth( REMOVED_LINES_WIDTH );
	size.setHeight( REMOVED_LINES_HEIGHT );
	
	removedLinesNumber->setGeometry( QRect( pos, size ) );
	
	//
	//LevelLabel
	//
	pos.setX( leftFreeSpaceCenter - getStringWidth( levelLabel->text() )/2 );
	pos.setY( height() - statusBarHeight - LEVEL_NUMBER_HEIGHT - getStringHeight() - 2*WIDGET_DISTANCE );
	
	//levelLabel->move( pos );
	size.setWidth( getStringWidth( levelLabel->text() ) );
	size.setHeight( getStringHeight() );
	levelLabel->setGeometry( QRect( pos, size ) );
	
	//
	//LevelNumber
	//
	pos.setX( leftFreeSpaceCenter - LEVEL_NUMBER_WIDTH/2 );
	pos.setY( height() - statusBarHeight - LEVEL_NUMBER_HEIGHT - WIDGET_DISTANCE );
	
	size.setWidth( LEVEL_NUMBER_WIDTH );
	size.setHeight( LEVEL_NUMBER_HEIGHT );
	
	levelNumber->setGeometry( QRect( pos, size ) );
	
	
	//   --Right part--
	int rightFreeSpaceCenter = centralTablePosOnX + newWidth + ( width() - newWidth )/4;
	
	
	//
	//NextShapeLabel
	//
	pos.setX( rightFreeSpaceCenter - getStringWidth( nextShapeLabel->text() )/2 );
	pos.setY( menuBarHeigth );
	
	cout << "nextShapeLabel width: " << nextShapeLabel->size().width() << endl;
	
	size.setWidth( getStringWidth( nextShapeLabel->text() ) );
	size.setHeight( getStringHeight() );
	nextShapeLabel->setGeometry( QRect( pos, size ) );
	
	//
	//NextShapeTable
	//
	nextShapeTable->setSquareSize( NEXT_SHAPE_SQUARE_SIZE );
	
	pos.setX( rightFreeSpaceCenter - NEXT_SHAPE_TABLE_SIZE/2 );
	pos.setY( menuBarHeigth + getStringHeight() + WIDGET_DISTANCE );
	
	size.setWidth( NEXT_SHAPE_TABLE_SIZE );
	size.setHeight( NEXT_SHAPE_TABLE_SIZE );
	
	nextShapeTable->setGeometry( QRect( pos, size ) );

}

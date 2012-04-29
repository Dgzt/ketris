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
#include <KDE/KApplication>
#include <KDE/KAboutData>
#include <KDE/KCmdLineArgs>
#include <KDE/KLocale>
#include <KDE/KIcon>
#include "mainwindow.h"


int main(int argc, char* argv[]){
  
    KAboutData aboutData( "ketris",
						  0,
						  ki18n("Ketris"),
						  "1.0.0",
						  ki18n("Ketris is a Tetris-like game."),
						  KAboutData::License_GPL_V3,
						  ki18n("(c) 2012 Zsuró Tibor")
						  );
	
	aboutData.setBugAddress("zsurotibor@gmail.com");
	
	aboutData.addAuthor( ki18n("Zsuró Tibor"),
						 ki18n("Developer and project founder"),
						 "zsurotibor" "@" "gmail" "." "com",
						 ""
					   );
    
    KCmdLineArgs::init( argc, argv, &aboutData );
    
    KApplication app;
    
    MainWindow *ketris = new MainWindow;
	ketris->setWindowIcon(KIcon("ketris"));
    ketris->show();
	
    return app.exec();
}

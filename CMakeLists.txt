project(ketris)

cmake_minimum_required(VERSION 2.6)

find_package(KDE4 "4.2" REQUIRED)
find_package(LibKDEGames REQUIRED)

include (KDE4Defaults)

include_directories(${KDE4_INCLUDES})
include_directories(${CMAKE_SOURCE_DIR}/libkdegames/highscore)

add_subdirectory( pics ) 
add_subdirectory( po )

MESSAGE(STATUS "${PROJECT_NAME} will be built to install into ${CMAKE_INSTALL_PREFIX}")

set(ketris_HDRS
	mainwindow.h
	shape.h
	table.h
	centraltable.h
	nextshapetable.h
)

set(ketris_SRCS 
	main.cpp
	mainwindow.cpp
	table.cpp
	shape.cpp
	centraltable.cpp
	nextshapetable.cpp
)

#
set(ketris_RCS
	ketris.qrc
)
#

add_definitions( -Wall )

# Only for Windows and Mac
kde4_add_app_icon(ketris_SRCS "hi*-app-ketris.png" )

qt4_add_resources( RCS ${ketris_RCS} )

kde4_add_executable(ketris ${ketris_SRCS} ${RCS} )

target_link_libraries(ketris ${KDE4_KDEUI_LIBS} kdegames)

#    -------INSTALL--------

SET(BIN_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/bin)
SET(XDG_APPS_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/share/applications/kde4/)
SET(ICON_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/share/icons/)


INSTALL(TARGETS  ${PROJECT_NAME}   DESTINATION     ${BIN_INSTALL_DIR})
INSTALL(FILES    ketris.desktop    DESTINATION     ${XDG_APPS_INSTALL_DIR})
INSTALL(FILES    ${ICO}            DESTINATION     ${ICON_INSTALL_DIR})
install(FILES    ketrisui.rc       DESTINATION     ${DATA_INSTALL_DIR}/ketris)

#-------------------------------------------------
#
# Project created by QtCreator 2017-09-27T14:18:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZorkGUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    GameData\main.cpp \
    GameData\Character.cpp \
    GameData\Command.cpp \
    GameData\CommandWords.cpp \
    GameData\item.cpp \
    GameData\Parser.cpp \
    GameData\Room.cpp \
    GameData\ZorkUL.cpp \
    GameData\player.cpp \
    GameView\MapWidget.cpp \
    GameView\mainwindow.cpp \
    GameView/itemwidget.cpp

HEADERS += \
    GameData\Character.h \
    GameData\Command.h \
    GameData\CommandWords.h \
    GameData\item.h \
    GameData\Parser.h \
    GameData\Room.h \
    GameData\ZorkUL.h \
    GameData\player.h \
    GameView\MapWidget.h \
    GameView\mainwindow.h \
    GameView/itemwidget.h

FORMS += \
        GameView\mainwindow.ui

RESOURCES += \
    resources.qrc

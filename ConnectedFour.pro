#-------------------------------------------------
#
# Project created by QtCreator 2018-12-03T13:22:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ConnectedFour
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        MainWindow.cpp \
    PlayerMenu.cpp \
    ClickableLabel.cpp \
    GameSquare.cpp \
    SizeFitGraphicsView.cpp \
    Disc.cpp

HEADERS  += MainWindow.hpp \
    PlayerMenu.hpp \
    ClickableLabel.hpp \
    GameSquare.hpp \
    SizeFitGraphicsView.hpp \
    common.hpp \
    Disc.hpp

FORMS    += MainWindow.ui \
    PlayerMenu.ui

RESOURCES += \
    icons.qrc

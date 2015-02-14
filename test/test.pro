#-------------------------------------------------
#
# Project created by QtCreator 2015-02-14T10:43:01
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    $$PWD/../src/sqlitedatabase.cpp

HEADERS += $$PWD/../src/sqlitedatabase.h

INCLUDEPATH += $$PWD/../src/

LIBS += -l$$PWD/../lib/Sqlite3_vs2010
INCLUDEPATH += $$PWD/../lib

DESTDIR = $$PWD/bin

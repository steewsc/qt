#-------------------------------------------------
#
# Project created by QtCreator 2013-10-19T22:04:37
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestingMemory
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    config.cpp \
    uploader.cpp \
    imageholder.cpp

HEADERS  += mainwindow.h \
    config.h \
    uploader.h \
    imageholder.h

FORMS    += mainwindow.ui

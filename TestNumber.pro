#-------------------------------------------------
#
# Project created by QtCreator 2015-02-25T12:37:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=gnu++11

TARGET = TestNumber
TEMPLATE = app

SOURCES += main.cpp\
    formwid.cpp \
    symbol.cpp \
    machinelearning.cpp \
    tinstance.cpp \
	tmetrics.cpp \
    tpool.cpp \
    tlinermodel.cpp \
    tleaner.cpp

HEADERS  += \
    formwid.h \
    symbol.h \
    machinelearning.h \
    tinstance.h \
	tmetrics.h \
    tpool.h \
    tlinermodel.h \
    tleaner.h

FORMS    += \
    formwid.ui

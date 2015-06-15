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
    tleaner.cpp \
    linerregress.cpp \
    adaboost.cpp \
    knn.cpp \
    alglib/linalg.cpp \
    alglib/alglibinternal.cpp \
    alglib/alglibmisc.cpp \
    alglib/ap.cpp \
    alglib/dataanalysis.cpp \
    alglib/diffequations.cpp \
    alglib/fasttransforms.cpp \
    alglib/interpolation.cpp \
    alglib/integration.cpp \
    alglib/optimization.cpp \
    alglib/solvers.cpp \
    alglib/specialfunctions.cpp \
    alglib/statistics.cpp \

HEADERS  += \
    formwid.h \
    symbol.h \
    machinelearning.h \
    tinstance.h \
    tmetrics.h \
    tpool.h \
    tlinermodel.h \
    tleaner.h \
    linerregress.h \
    adaboost.h \
    knn.h  \
    alglib/linalg.h \
    alglib/linalg.h \
    alglib/alglibinternal.h \
    alglib/alglibmisc.h \
    alglib/ap.h \
    alglib/dataanalysis.h \
    alglib/diffequations.h \
    alglib/fasttransforms.h \
    alglib/interpolation.h \
    alglib/integration.h \
    alglib/optimization.h \
    alglib/solvers.h \
    alglib/specialfunctions.h \
    alglib/statistics.h \

FORMS    += \
    formwid.ui

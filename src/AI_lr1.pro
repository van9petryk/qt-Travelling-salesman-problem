#-------------------------------------------------
#
# Project created by QtCreator 2016-02-20T15:06:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AI_lr1
TEMPLATE = app

SOURCES += main.cpp\
    mapframe.cpp \
    mainwidget.cpp \
    distancematrix.cpp \
    squarematrix.cpp \
    crossover.cpp \
    mutation.cpp \
    tsp_model.cpp \
    toursinfo.cpp \
    tsp_historymodel.cpp \
    random.cpp

HEADERS  += \
    mapframe.h \
    mainwidget.h \
    distancematrix.h \
    squarematrix.h \
    crossover.h \
    mutation.h \
    tsp_model.h \
    toursinfo.h \
    tsp_historymodel.h \
    random.h


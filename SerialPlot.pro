#-------------------------------------------------
#
# Project created by QtCreator 2014-06-29T09:39:39
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialPlot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serialplotter.cpp \
    paintwidget.cpp

HEADERS  += mainwindow.h \
    serialplotter.h \
    paintwidget.h

FORMS    += mainwindow.ui

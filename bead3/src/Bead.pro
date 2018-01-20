#-------------------------------------------------
#
# Project created by QtCreator 2016-05-23T14:58:07
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bead
TEMPLATE = app


SOURCES += main.cpp\
        eventlistwidget.cpp \
    teremtablemodel.cpp \
    esemenytablemodel.cpp \
    eventrentdialog.cpp \
    esemenytabledelegate.cpp \
    mainwindow.cpp \
    renttablemodel.cpp \
    tableeditorwidget.cpp

HEADERS  += eventlistwidget.h \
    teremtablemodel.h \
    esemenytablemodel.h \
    esemenytabledelegate.h \
    eventrentdialog.h \
    mainwindow.h \
    renttablemodel.h \
    tableeditorwidget.h

FORMS    += eventlistwidget.ui \
    eventrentdialog.ui

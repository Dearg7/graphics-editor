#-------------------------------------------------
#
# Project created by QtCreator 2016-04-03T19:59:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraphicsEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imageitem.cpp \
    tools/penciltool.cpp \
    widgets/colorselection.cpp \
    undostack.cpp \
    tools/erasertool.cpp \
    tools/ellipsetool.cpp


HEADERS  += mainwindow.h \
    imageitem.h \
    tools/penciltool.h \
    widgets/colorselection.h \
    undostack.h \
    tools/erasertool.h \
    tools/ellipsetool.h


FORMS    += mainwindow.ui

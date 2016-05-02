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
    tools/ellipsetool.cpp \
    tools/rectangletool.cpp \
    tools/linetool.cpp \
    tools/curvelinetool.cpp \
    tools/filltool.cpp \
    tools/pipettetool.cpp


HEADERS  += mainwindow.h \
    imageitem.h \
    tools/penciltool.h \
    widgets/colorselection.h \
    undostack.h \
    tools/erasertool.h \
    tools/ellipsetool.h \
    tools/rectangletool.h \
    tools/linetool.h \
    tools/curvelinetool.h \
    tools/filltool.h \
    tools/pipettetool.h


FORMS    += mainwindow.ui

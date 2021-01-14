#-------------------------------------------------
#
# Project created by QtCreator 2021-01-30T12:53:03
#
#-------------------------------------------------

QT += core widgets gui webengine webenginewidgets svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tetris
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/widget.cpp

HEADERS  += src/mainwindow.h \
    src/widget.h

CONFIG += link_pkgconfig
PKGCONFIG += dtkwidget

CONFIG += c++11

FORMS += \
    src/widget.ui

RESOURCES += \
    src/resources.qrc

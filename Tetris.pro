#-------------------------------------------------
#
# Project created by QtCreator 2021-01-30T12:53:03
#
#-------------------------------------------------

QT += core widgets gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tetris
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/widget.cpp \
    src/tetrisgame.cpp \
    src/gameboard.cpp \
    src/nextpiecewidget.cpp

HEADERS  += src/mainwindow.h \
    src/widget.h \
    src/tetrisgame.h \
    src/gameboard.h \
    src/nextpiecewidget.h

CONFIG += link_pkgconfig
PKGCONFIG += dtkwidget

CONFIG += c++11 lrelease embed_translations
QM_FILES_RESOURCE_PREFIX = /translations

FORMS += \
    src/widget.ui

RESOURCES += \
    src/resources.qrc

TRANSLATIONS = \
    translations/tetris_es.ts \
    translations/tetris_fr.ts \
    translations/tetris_de.ts \
    translations/tetris_pt.ts


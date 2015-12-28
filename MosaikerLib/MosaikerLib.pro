#-------------------------------------------------
#
# Project created by QtCreator 2015-12-28T16:31:20
#
#-------------------------------------------------
include(../include.pri)

QT       -= gui

TARGET = MosaikerLib

TEMPLATE = lib
CONFIG += staticlib

SOURCES += ResourceFinder.cpp \
    ResourceIndexBuilder.cpp \
    ImageManipulator.cpp

HEADERS += ResourceFinder.h \
    ResourceIndexBuilder.h \
    ImageLibraryAdapter.h \
    ImageManipulator.h
    Exceptions.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

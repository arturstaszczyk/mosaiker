#-------------------------------------------------
#
# Project created by QtCreator 2015-12-28T16:31:20
#
#-------------------------------------------------
include(../include.pri)

QT       += gui widgets

TARGET = MosaikerLib

TEMPLATE = lib
CONFIG += staticlib

SOURCES += ResourceFinder.cpp \
    ResourceIndexBuilder.cpp \
    ImageManipulator.cpp \
    Commands/Command.cpp \
    Commands/CommandOpenImage.cpp \
    ImageManipulatorBuilder.cpp

HEADERS += ResourceFinder.h \
    ResourceIndexBuilder.h \
    ImageManipulator.h \
    Commands/Command.h \
    Commands/CommandOpenImage.h \
    Interfaces/ImageManipulatorInt.h \
    Exceptions.h \
    Interfaces/ImageLibraryAdapterInt.h \
    ImageManipulatorBuilder.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

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
    ImageManipulatorBuilder.cpp \
    ImageLibs/ImageLibraryDevIL.cpp \
    FileChooser.cpp

HEADERS += ResourceFinder.h \
    ResourceIndexBuilder.h \
    ImageManipulator.h \
    Commands/Command.h \
    Commands/CommandOpenImage.h \
    Interfaces/ImageManipulatorInt.h \
    Exceptions.h \
    Interfaces/ImageLibraryAdapterInt.h \
    ImageManipulatorBuilder.h \
    Interfaces/IFileChooser.h \
    ImageLibs/ImageLibraryDevIL.h \
    FileChooser.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:INCLUDEPATH += /usr/local/Cellar/devil/1.7.8_1/include
else:error(Not implemented)

#QMAKE_CXXFLAGS += -g -Wall -fprofile-arcs -ftest-coverage -O0
#QMAKE_LFLAGS += -g -Wall -fprofile-arcs -ftest-coverage  -O0

#-------------------------------------------------
#
# Project created by QtCreator 2015-12-28T16:31:20
#
#-------------------------------------------------
include(../include.pri)

QT       += gui widgets quick

TARGET = MosaikerLib

TEMPLATE = lib
CONFIG += staticlib

SOURCES += ResourceFinder.cpp \
    ResourceIndexBuilder.cpp \
    FileChooser.cpp \
    Commands/CommandOpenImage.cpp \
    Commands/Command.cpp \
    Models/ImageModel.cpp

HEADERS += ResourceFinder.h \
    Exceptions.h \
    FileChooser.h \
    ResourceIndexBuilder.h \
    Interfaces/IFileChooser.h \
    Commands/CommandOpenImage.h \
    Commands/Command.h \
    Models/ImageModel.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:INCLUDEPATH += /usr/local/Cellar/devil/1.7.8_1/include
else:error(Not implemented)

#QMAKE_CXXFLAGS += -g -Wall -fprofile-arcs -ftest-coverage -O0
#QMAKE_LFLAGS += -g -Wall -fprofile-arcs -ftest-coverage  -O0

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
    Models/ImageModel.cpp \
    Commands/CommandOpenResourcesDir.cpp \
    Models/ResourcesDirModel.cpp \
    Commands/CommandBuildIndex.cpp \
    ImageIndexer.cpp

HEADERS += ResourceFinder.h \
    Exceptions.h \
    FileChooser.h \
    ResourceIndexBuilder.h \
    Interfaces/IFileChooser.h \
    Commands/CommandOpenImage.h \
    Commands/Command.h \
    Models/ImageModel.h \
    Commands/CommandOpenResourcesDir.h \
    Models/ResourcesDirModel.h \
    Commands/CommandBuildIndex.h \
    Interfaces/IResourceFinder.h \
    ImageIndexer.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
else:win32: {
    target.path = $$PWD/lib
    INSTALLS += target
}

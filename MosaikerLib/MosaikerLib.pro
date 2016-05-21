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
    FileChooser.cpp \
    Commands/CommandOpenImage.cpp \
    Commands/Command.cpp \
    Commands/CommandOpenResourcesDir.cpp \
    Models/ResourcesDirModel.cpp \
    Commands/CommandBuildIndex.cpp \
    ImageIndexer.cpp \
    Models/ProgressBarModel.cpp \
    Commands/CommandRecycler.cpp \
    Models/MainImageModel.cpp \
    Commands/CommandCreateMosaic.cpp \
    IndexBuilder.cpp \
    ImageSlicer.cpp

HEADERS += ResourceFinder.h \
    Exceptions.h \
    FileChooser.h \
    Interfaces/IFileChooser.h \
    Commands/CommandOpenImage.h \
    Commands/Command.h \
    Commands/CommandOpenResourcesDir.h \
    Models/ResourcesDirModel.h \
    Commands/CommandBuildIndex.h \
    Interfaces/IResourceFinder.h \
    ImageIndexer.h \
    Models/ProgressBarModel.h \
    Commands/CommandRecycler.h \
    Models/MainImageModel.h \
    Commands/CommandCreateMosaic.h \
    Interfaces/IIndexBuilder.h \
    IndexBuilder.h \
    Interfaces/IImageSlicer.h \
    ImageSlicer.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
else:win32: {
    target.path = $$PWD/lib
    INSTALLS += target
}

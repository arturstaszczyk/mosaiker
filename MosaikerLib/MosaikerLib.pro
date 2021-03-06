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

SOURCES += FileSystemOps/ResourceFinder.cpp \
    FileSystemOps/FileChooser.cpp \
    Commands/CommandOpenImage.cpp \
    Commands/Command.cpp \
    Commands/CommandOpenResourcesDir.cpp \
    Models/ResourcesDirModel.cpp \
    Commands/CommandBuildIndex.cpp \
    IndexingOps/ImageIndexer.cpp \
    Models/ProgressBarModel.cpp \
    Commands/CommandRecycler.cpp \
    Commands/CommandCreateMosaic.cpp \
    IndexingOps/IndexBuilder.cpp \
    ImageOps/ImageSlicer.cpp \
    IndexingOps/IndexLoader.cpp \
    ImageOps/ImageCreator.cpp \
    Models/MosaicBuildButtonModel.cpp \
    Models/PictureModel.cpp \
    Commands/CommandSaveMosaic.cpp \
    Models/MatcherModel.cpp \
    IndexingOps/IndexMatcherDistance.cpp \
    IndexingOps/IndexMatcherFactory.cpp \
    IndexingOps/IndexMatcherGreedy.cpp \
    Models/SliceSizeModel.cpp

HEADERS += FileSystemOps/ResourceFinder.h \
    Exceptions.h \
    FileSystemOps/FileChooser.h \
    Interfaces/IFileChooser.h \
    Commands/CommandOpenImage.h \
    Commands/Command.h \
    Commands/CommandOpenResourcesDir.h \
    Models/ResourcesDirModel.h \
    Commands/CommandBuildIndex.h \
    Interfaces/IResourceFinder.h \
    IndexingOps/ImageIndexer.h \
    Models/ProgressBarModel.h \
    Commands/CommandRecycler.h \
    Commands/CommandCreateMosaic.h \
    Interfaces/IIndexBuilder.h \
    IndexingOps/IndexBuilder.h \
    Interfaces/IImageSlicer.h \
    ImageOps/ImageSlicer.h \
    Interfaces/IIndexLoader.h \
    IndexingOps/IndexLoader.h \
    ImageOps/ImageCreator.h \
    Models/MosaicBuildButtonModel.h \
    Models/PictureModel.h \
    Commands/CommandSaveMosaic.h \
    HptIntegration.h \
    Interfaces/IIndexMatcherStrategy.h \
    Models/MatcherModel.h \
    IndexingOps/IndexMatcherGreedy.h \
    IndexingOps/IndexMatcherFactory.h \
    IndexingOps/IndexMatcherDistance.h \
    Models/SliceSizeModel.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
else:win32: {
    target.path = $$PWD/lib
    INSTALLS += target
}

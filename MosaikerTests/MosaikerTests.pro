#-------------------------------------------------
#
# Project created by QtCreator 2015-12-28T16:32:47
#
#-------------------------------------------------

include(../include.pri)

QT       += testlib

QT       -= gui

TARGET = tst_MosaikerTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    tst_ResourceFinderTest.cpp \
    tst_ResourceIndexBuilderTest.cpp \
    mocks/ImageLibraryAdapterMock.cpp \
    tst_ImageManipulatorTest.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

unix|win32: LIBS += -L$$OUT_PWD/../MosaikerLib/ -lMosaikerLib

INCLUDEPATH += $$PWD/../MosaikerLib
DEPENDPATH += $$PWD/../MosaikerLib

win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../MosaikerLib/MosaikerLib.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../MosaikerLib/libMosaikerLib.a

win32: {
    error("Not implemented")
}
else:unix: {
    copyfiles.commands = cp -rf $$PWD/TestResources $$OUT_PWD
}

QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles

HEADERS += \
    tst_ResourceFinderTest.h \
    mocks/ImageLibraryAdapterMock.h \
    tst_ImageManipulatorTest.h \
    mocks/MockBase.h

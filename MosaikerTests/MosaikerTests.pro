#-------------------------------------------------
#
# Project created by QtCreator 2015-12-28T16:32:47
#
#-------------------------------------------------

include(../include.pri)

QT       += testlib widgets gui quick

TARGET = tst_MosaikerTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    tst_ResourceFinderTest.cpp \
    tst_ResourceIndexBuilderTest.cpp \
    tst_CommandOpenImageTest.cpp \
    tst_ImageModel.cpp \
    tst_CommandOpenResourcesDirTest.cpp \
    tst_ResourcesDirModelTest.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

unix|win32: LIBS += -L$$OUT_PWD/../MosaikerLib/ -lMosaikerLib

INCLUDEPATH += $$PWD/../MosaikerLib $$PWD/TestLibs/QtMock
LIBS += -L$$PWD/TestLibs/QtMock -lQtMock
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
    tst_CommandOpenImageTest.h \
    tst_Common.h \
    mocks/QFileDialogMock.h \
    mocks/FileChooserMock.h \
    tst_ImageModel.h \
    tst_CommandOpenResourcesDirTest.h \
    tst_ResourcesDirModelTest.h

#https://www.cocoanetics.com/2013/10/xcode-coverage/
#http://mgrebenets.github.io/mobile%20ci/2015/09/21/code-coverage-for-ios-xcode-7/
#http://www.robertwloch.net/2013/06/generating-lcov-coverage-with-qtcreator/
#QMAKE_CXXFLAGS += -g -Wall -fprofile-arcs -ftest-coverage -O0
#QMAKE_LFLAGS += -g -Wall -fprofile-arcs -ftest-coverage  -O0


#-------------------------------------------------
#
# Project created by QtCreator 2015-12-28T16:31:53
#
#-------------------------------------------------

include(../include.pri)

QT       += core gui quick quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MosaikeApp
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.h

FORMS    += MainWindow.ui

RESOURCES += \
    qmlResources.qrc

unix|win32: LIBS += -L$$OUT_PWD/../MosaikerLib/ -lMosaikerLib

INCLUDEPATH += $$PWD/../MosaikerLib
DEPENDPATH += $$PWD/../MosaikerLib

win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../MosaikerLib/MosaikerLib.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../MosaikerLib/libMosaikerLib.a

# DevIL
unix:INCLUDEPATH += /usr/local/Cellar/devil/1.7.8_1/include
else:error(Not implemented)
unix:LIBS += -L/usr/local/Cellar/devil/1.7.8_1/lib -lIL -lILU -lILUT

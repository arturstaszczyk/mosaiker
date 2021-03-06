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

win32: {
    CONFIG(debug, debug|release) {
        LIBS += -L$$OUT_PWD/../MosaikerLib/debug
    }
    else {
        LIBS += -L$$OUT_PWD/../MosaikerLib/release
    }
}

unix: {
    CONFIG(debug, debug|release) {
        LIBS += -L$$OUT_PWD/../MosaikerLib
    }
    else {
        LIBS += -L$$OUT_PWD/../MosaikerLib
    }
}
unix|win32: LIBS += -lMosaikerLib

INCLUDEPATH += $$PWD/../MosaikerLib
DEPENDPATH += $$PWD/../MosaikerLib

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../MosaikerLib/lib/MosaikerLib.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../MosaikerLib/libMosaikerLib.a

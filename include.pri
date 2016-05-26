CONFIG += c++11 warn_on rtti exceptions

macx {
    QMAKE_MAC_SDK = macosx10.11
}

profile {
    INCLUDEPATH += $$PWD/externals
    LIBS += -L$$PWD/externals/HPT -lHighPerformanceTimer
    DEFINES += _PROFILE
}

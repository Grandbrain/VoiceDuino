QT          += core gui widgets multimedia network
TARGET      = VoiceDuino
TEMPLATE    = app
SOURCES     += main.cpp window.cpp recognition.cpp string2number.cpp
HEADERS     += window.h recognition.h string2number.h
FORMS       += window.ui
RESOURCES   += resources.qrc
RC_ICONS    = Resources/icon.ico
INCLUDEPATH += $$PWD/../../External/sphinx/include
DEPENDPATH  += $$PWD/../../External/sphinx/include

win32 {
    CONFIG(debug, debug|release) {
        contains(QT_ARCH, i386) {
            LIBS += -L$$PWD/../../External/sphinx/lib/windows/32bit/debug/ -lsphinxbase
            LIBS += -L$$PWD/../../External/sphinx/lib/windows/32bit/debug/ -lpocketsphinx
        } else {
            LIBS += -L$$PWD/../../External/sphinx/lib/windows/64bit/debug/ -lsphinxbase
            LIBS += -L$$PWD/../../External/sphinx/lib/windows/64bit/debug/ -lpocketsphinx
        }
    } else {
        contains(QT_ARCH, i386) {
            LIBS += -L$$PWD/../../External/sphinx/lib/windows/32bit/release/ -lsphinxbase
            LIBS += -L$$PWD/../../External/sphinx/lib/windows/32bit/release/ -lpocketsphinx
        } else {
            LIBS += -L$$PWD/../../External/sphinx/lib/windows/64bit/release/ -lsphinxbase
            LIBS += -L$$PWD/../../External/sphinx/lib/windows/64bit/release/ -lpocketsphinx
        }
    }
}

#-------------------------------------------------
#
# Project created by QtCreator 2011-09-11T22:13:55
#
#-------------------------------------------------

QT       += core gui

TARGET = PDI
TEMPLATE = app


SOURCES += main.cpp\
        pdi.cpp \
    sobre.cpp \
    VC/mediaimg.cpp \
    dialogmedia.cpp

HEADERS  += pdi.h \
    sobre.h \
    VC/mediaimg.h \
    dialogmedia.h

FORMS    += pdi.ui \
    sobre.ui \
    VC/mediaimg.ui \
    dialogmedia.ui

RESOURCES += \
    img.qrc

INCLUDEPATH += C:/opencv/build/include/

LIBS += C:/opencv/build/bin/*.dll

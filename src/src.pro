TEMPLATE = app
TARGET = $$OUT_PWD/test

CONFIG += link_pkgconfig
#PKGCONFIG += 
LIBS += /usr/lib/pnglite.o -lz

#QT -= gui

INCLUDEPATH += .

#HEADERS +=

SOURCES += \
  main.cpp

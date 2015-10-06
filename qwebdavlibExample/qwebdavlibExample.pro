QT       += core network xml

QT       -= gui

TARGET = testConsole
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    qexample.cpp

# Enable extended WebDAV properties (see QWebDavItem.h/cpp)
DEFINES += QWEBDAVITEM_EXTENDED_PROPERTIES

include($${PWD}/../qwebdavlib/qwebdavlib.pri)

HEADERS += \
    qexample.h

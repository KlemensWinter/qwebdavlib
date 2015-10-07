#-------------------------------------------------
#
# Project created by QtCreator 2015-10-07T17:55:11
#
#-------------------------------------------------

QT       += network xml testlib

QT       -= gui

TARGET = tst_webdavtests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

# Enable extended WebDAV properties (see QWebDavItem.h/cpp)
DEFINES += QWEBDAVITEM_EXTENDED_PROPERTIES

include($${PWD}/../qwebdavlib/qwebdavlib.pri)


SOURCES += tst_webdavtests.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

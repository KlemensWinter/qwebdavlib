
# for a qwebdavlib without support for GUI
QT       -= gui

TARGET = qwebdav
TEMPLATE = lib


QMAKE_CXXFLAGS += -Wno-overloaded-virtual

# Enable DEBUG output with qDebug()
#DEFINES += DEBUG_WEBDAV

# Enable extended WebDAV properties (see QWebDavItem.h/cpp)
DEFINES += QWEBDAVITEM_EXTENDED_PROPERTIES

# build shared library
DEFINES += QWEBDAVLIB_BUILD_SHARED
DEFINES += QWEBDAV_LIBRARY

include($${PWD}/qwebdavlib.pri)

OTHER_FILES += \
    CHANGES \
    LICENSE \
    README

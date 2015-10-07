QT       += network xml

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += $${PWD}

SOURCES += \
    $${PWD}/qwebdav.cpp \
    $${PWD}/qwebdavitem.cpp \
    $${PWD}/qwebdavdirparser.cpp \
    $${PWD}/qnaturalsort.cpp

HEADERS += \
    $${PWD}/qwebdav.h \
    $${PWD}/qwebdavitem.h \
    $${PWD}/qwebdavdirparser.h \
    $${PWD}/qnaturalsort.h \
    $${PWD}/qwebdav_global.h


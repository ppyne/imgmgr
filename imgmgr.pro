#-------------------------------------------------
#
# Project created by QtCreator 2018-03-03T02:10:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = imgmgr
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    application.cpp \
    mdisubwindow.cpp \
    graphicsview.cpp \
    graphicsscene.cpp \
    image.cpp \
    graphicspixmapitem.cpp \
    zoombox.cpp \
    dialognew.cpp \
    fimage.cpp \
    fgraphicsitem.cpp \
    fcolor.cpp

HEADERS  += mainwindow.h \
    application.h \
    mdisubwindow.h \
    graphicsview.h \
    graphicsscene.h \
    image.h \
    graphicspixmapitem.h \
    zoombox.h \
    dialognew.h \
    fimage.h \
    fgraphicsitem.h \
    fcolor.h

FORMS    += mainwindow.ui \
    dialognew.ui

RESOURCES += \
    resources.qrc

ICON = imgmgr.icns
QMAKE_INFO_PLIST = imgmgr.plist
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.14


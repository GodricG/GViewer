#-------------------------------------------------
#
# Project created by QtCreator 2014-05-01T14:24:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gviewer
TEMPLATE = app


SOURCES += main.cpp\
        gviewer.cpp \
        radar.cpp \
        src/src/*
        

HEADERS  += gviewer.h src/include/* \
    radar.h


FORMS    += gviewer.ui 

INCLUDEPATH += /usr/include/vtk-6.3
LIBS += /usr/lib/x86_64-linux-gnu/libvtk*.so

INCLUDEPATH += /usr/include/boost
LIBS += /Apps/boost168/lib/libboost_*.so

INCLUDEPATH += /Apps/PCL191/include/pcl-1.9
LIBS += /Apps/PCL191/lib/libpcl_*.so

INCLUDEPATH += src/include ##radar headers

DISTFILES += \
    CMakeLists.txt

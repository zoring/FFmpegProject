QT += core
QT -= gui
include(../libmaia-master/maia.pri)
CONFIG += c++11
CONFIG   += link_pkgconfig
PKGCONFIG += libavformat libavcodec libavfilter libavutil
TARGET = EducationInspection
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    handleffmpeg.cpp \
    ffmpegthread.cpp \
    service.cpp

HEADERS += \
    handleffmpeg.h \
    ffmpegthread.h \
    service.h

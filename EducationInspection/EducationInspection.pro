QT += core
QT -= gui

CONFIG += c++11
CONFIG   += link_pkgconfig
PKGCONFIG += libavformat libavcodec libavfilter libavutil
TARGET = EducationInspection
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    handleffmpeg.cpp \
    ffmpegthread.cpp

HEADERS += \
    handleffmpeg.h \
    ffmpegthread.h

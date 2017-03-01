QT += core
QT -= gui

CONFIG += c++11

TARGET = scanner
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    scanner.cpp \
    token.cpp

HEADERS += \
    scanner.h \
    token.h \
    myexception.h

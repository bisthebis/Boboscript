TARGET = scannerlib
TEMPLATE = lib
CONFIG += staticlib

SOURCES = command_line.cpp \
    scanner.cpp \
    token.cpp

HEADERS = command_line.h \
    myexception.h \
    token.h \
    scanner.h

DESTDIR = ../scannerlib

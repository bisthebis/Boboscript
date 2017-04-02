QT += testlib
TARGET = tests
TEMPLATE = app
SOURCES = main.cpp \
    lexertest.cpp
HEADERS += \
    lexertest.h
INCLUDEPATH += ../scannerlib
LIBS += -L../scannerlib -lscannerlib


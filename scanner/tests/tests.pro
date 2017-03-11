QT += testlib
TARGET = tests
TEMPLATE = app
SOURCES = dummytest.cpp
INCLUDEPATH += ../scannerlib
LIBS += -L../scannerlib -lscannerlib

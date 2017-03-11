QT += core testlib
QT -= gui

CONFIG += c++14
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = subdirs

SUBDIRS = app scannerlib tests

app.depends = scannerlib
test.depends = scannerlib

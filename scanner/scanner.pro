QT += core testlib
QT -= gui

CONFIG += c++14
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = subdirs

SUBDIRS = app scannerlib

app.depends = scannerlib

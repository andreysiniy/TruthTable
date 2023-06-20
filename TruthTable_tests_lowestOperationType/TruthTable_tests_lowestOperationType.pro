QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_lowestoperationtype_tests.cpp \
            ../TruthTable_project/node.cpp

HEADERS +=  ../TruthTable_project/node.h


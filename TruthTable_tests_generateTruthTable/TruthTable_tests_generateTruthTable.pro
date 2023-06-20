QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_generatetruthtable_tests.cpp \
            ../TruthTable_project/node.cpp \
            ../TruthTable_project/errorhandler.cpp \
            ../TruthTable_project/truthtable.cpp \
            ../TruthTable_project/stringoperations.cpp


HEADERS +=  ../TruthTable_project/node.h \
            ../TruthTable_project/errorhandler.h \
            ../TruthTable_project/truthtable.h \
            ../TruthTable_project/stringoperations.h

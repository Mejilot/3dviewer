include(gtest_dependency.pri)
QT += core gui
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG += qt

SOURCES += \
        ../../viewer/parser.h ../../viewer/affine.h ../../viewer/dataclass.h \
        ../../viewer/parser.cc ../../viewer/affine.cc ../../viewer/dataclass.cc \
        main.cc \
        tst_parser_1.cc

######################################################################
# Automatically generated by qmake (2.01a) Thu Feb 7 19:36:18 2008
######################################################################

CONFIG += qtestlib
TEMPLATE = app
TARGET = ../bin/tests
DEPENDPATH += . 
INCLUDEPATH += . ../src

LIBS += -L../bin/ -llidarconverter

# Input
HEADERS += testdatasource.h \
	   datasourcetests.h \
	   segmenttests.h \
	   testhelper.h
SOURCES += datasourcetests.cpp \ 
	   testdatasource.cpp \
	   segmenttests.cpp \
	   tests.cpp \
	   testhelper.cpp

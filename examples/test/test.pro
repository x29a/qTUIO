unix {
LIBS += -L../../lib -lqTUIO
INCLUDEPATH += ../../src
}
win32:LIBS += -lqTUIO

TEMPLATE = app
TARGET = test

HEADERS += test.h
SOURCES += main.cpp \
    test.cpp

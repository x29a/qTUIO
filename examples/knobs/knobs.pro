unix {
LIBS += -L../../lib -lqTUIO
INCLUDEPATH += ../../src
}
win32:LIBS += -lqTUIO
HEADERS += knob.h
SOURCES += main.cpp \
    knob.cpp

unix {
LIBS += -L../../lib -lqTUIO
INCLUDEPATH += ../../src
}
win32:LIBS += -lqTUIO

SOURCES += main.cpp
 FORMS += dials.ui
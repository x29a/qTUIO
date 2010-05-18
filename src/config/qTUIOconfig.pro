unix {
LIBS += -L../../lib -lqTUIO
INCLUDEPATH += ../
}
win32:LIBS += -lqTUIO

SOURCES += main.cpp \
    cross.cpp
HEADERS += cross.h
QT += xml

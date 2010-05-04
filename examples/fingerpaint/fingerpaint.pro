unix { 
    LIBS += -L../../lib \
        -lqTUIO
    INCLUDEPATH += ../../src
}
win32:LIBS += -lTuioToQt

HEADERS += mainwindow.h \
    scribblearea.h 
SOURCES += main.cpp \
    mainwindow.cpp \
    scribblearea.cpp 

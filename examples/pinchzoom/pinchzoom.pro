unix {
LIBS += -L../../lib -lqTUIO
INCLUDEPATH += ../../src
}
win32:LIBS += -lqTUIO

HEADERS += graphicsview.h \
    mouse.h 
SOURCES += graphicsview.cpp \
    main.cpp \
    mouse.cpp 
RESOURCES += mice.qrc

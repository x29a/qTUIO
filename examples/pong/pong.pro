unix { 
    LIBS += -L../../lib \
        -lqTUIO
    INCLUDEPATH += ../../src
}
win32:LIBS += -lqTUIO
QT += opengl
TEMPLATE = app
TARGET = pong
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += spectator.h \
    ball.h \
    player.h \
    pong.h
SOURCES += spectator.cpp \
    ball.cpp \
    player.cpp \
    main.cpp \
    pong.cpp

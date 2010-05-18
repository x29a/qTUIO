# Name of the application
TEMPLATE = lib
TARGET = qTUIO

# Qt modules required
QT += core \
    gui \
    network \
    xml
	
# Small configurations
CONFIG += precompile_header
win32:CONFIG += embed_manifest_exe
DEFINES += OSC_HOST_LITTLE_ENDIAN

# Windows libraries for OSC Pack
win32:LIBS += ws2_32.lib \
    winmm.lib

# Changes the name of the target, when is debug mode
CONFIG( debug, debug|release ) { 
    TARGET = $${TARGET}_d
    BUILD_NAME = debug
}
CONFIG( release, debug|release ):BUILD_NAME = release

# Temporary folders for the auxiliar files
INCLUDEPATH += ../tmp/$$BUILD_NAME \
    ../tmp
OBJECTS_DIR = ../tmp/$$BUILD_NAME
MOC_DIR = ../tmp/$$BUILD_NAME
UI_DIR = ../tmp
RCC_DIR = ../tmp
DESTDIR = ../lib

# External files for the project
include( 3rdparty.pri )

# Main project files
HEADERS += qtuio_dll.h \
    qtuio.h
SOURCES += qtuio.cpp

# Resources
RESOURCES += 

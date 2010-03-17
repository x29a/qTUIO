TEMPLATE = app
TARGET = qTUIO
DESTDIR = bin/
OBJECTS_DIR = build/
MOC_DIR = build/
UI_DIR = build/
RCC_DIR = build/
QT += core \
    gui \
    xml \
    network \
    opengl
INCLUDEPATH += include/ \
    src/3rdparty/oscpack \
    src/3rdparty/sdl \
    src/3rdparty/tuio
HEADERS += src/tuiointerface.h \
    src/qtuio.h \
    src/3rdparty/oscpack/ip/IpEndpointName.h \
    src/3rdparty/oscpack/ip/NetworkingUtils.h \
    src/3rdparty/oscpack/ip/PacketListener.h \
    src/3rdparty/oscpack/ip/TimerListener.h \
    src/3rdparty/oscpack/ip/UdpSocket.h \
    src/3rdparty/oscpack/osc/MessageMappingOscPacketListener.h \
    src/3rdparty/oscpack/osc/OscException.h \
    src/3rdparty/oscpack/osc/OscHostEndianness.h \
    src/3rdparty/oscpack/osc/OscOutboundPacketStream.h \
    src/3rdparty/oscpack/osc/OscPacketListener.h \
    src/3rdparty/oscpack/osc/OscPrintReceivedElements.h \
    src/3rdparty/oscpack/osc/OscReceivedElements.h \
    src/3rdparty/oscpack/osc/OscTypes.h \
    src/3rdparty/tuio/TuioClient.h \
    src/3rdparty/tuio/TuioContainer.h \
    src/3rdparty/tuio/TuioCursor.h \
    src/3rdparty/tuio/TuioListener.h \
    src/3rdparty/tuio/TuioObject.h \
    src/3rdparty/tuio/TuioPoint.h \
    src/3rdparty/tuio/TuioServer.h \
    src/3rdparty/tuio/TuioTime.h
SOURCES += src/3rdparty/tuio/TuioClient.cpp \
    src/3rdparty/tuio/TuioServer.cpp \
    src/3rdparty/tuio/TuioTime.cpp \
    src/3rdparty/oscpack/osc/OscTypes.cpp \
    src/3rdparty/oscpack/osc/OscOutboundPacketStream.cpp \
    src/3rdparty/oscpack/osc/OscReceivedElements.cpp \
    src/3rdparty/oscpack/osc/OscPrintReceivedElements.cpp \
    src/3rdparty/oscpack/ip/posix/NetworkingUtils.cpp \
    src/3rdparty/oscpack/ip/posix/UdpSocket.cpp \
    src/tuiointerface.cpp \
    src/main.cpp \
    src/qtuio.cpp
FORMS += tuiointerface.ui \
    qtuio.ui
RESOURCES += 
DEFINES += OSC_HOST_LITTLE_ENDIAN

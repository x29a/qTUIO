# Paths
INCLUDEPATH += \
    3rdparty/oscpack \
    3rdparty/tuio

# Files
HEADERS += 3rdparty/oscpack/ip/IpEndpointName.h \
    3rdparty/oscpack/ip/NetworkingUtils.h \
    3rdparty/oscpack/ip/PacketListener.h \
    3rdparty/oscpack/ip/TimerListener.h \
    3rdparty/oscpack/ip/UdpSocket.h \
    3rdparty/oscpack/osc/MessageMappingOscPacketListener.h \
    3rdparty/oscpack/osc/OscException.h \
    3rdparty/oscpack/osc/OscHostEndianness.h \
    3rdparty/oscpack/osc/OscOutboundPacketStream.h \
    3rdparty/oscpack/osc/OscPacketListener.h \
    3rdparty/oscpack/osc/OscPrintReceivedElements.h \
    3rdparty/oscpack/osc/OscReceivedElements.h \
    3rdparty/oscpack/osc/OscTypes.h \
    3rdparty/tuio/TuioClient.h \
    3rdparty/tuio/TuioContainer.h \
    3rdparty/tuio/TuioCursor.h \
    3rdparty/tuio/TuioListener.h \
    3rdparty/tuio/TuioObject.h \
    3rdparty/tuio/TuioPoint.h \
    3rdparty/tuio/TuioServer.h \
    3rdparty/tuio/TuioTime.h
SOURCES += 3rdparty/tuio/TuioClient.cpp \
    3rdparty/tuio/TuioServer.cpp \
    3rdparty/tuio/TuioTime.cpp \
    3rdparty/oscpack/osc/OscTypes.cpp \
    3rdparty/oscpack/osc/OscOutboundPacketStream.cpp \
    3rdparty/oscpack/osc/OscReceivedElements.cpp \
    3rdparty/oscpack/osc/OscPrintReceivedElements.cpp
# files for Windows
win32:SOURCES += 3rdparty/oscpack/ip/win32/NetworkingUtils.cpp \
    3rdparty/oscpack/ip/win32/UdpSocket.cpp
# files for Unix
unix:SOURCES += 3rdparty/oscpack/ip/posix/NetworkingUtils.cpp \
    3rdparty/oscpack/ip/posix/UdpSocket.cpp

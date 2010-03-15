TEMPLATE = app
TARGET = qTUIO
QT += core \
    gui \
    xml \
    network \
    opengl
INCLUDEPATH += include/ \
    src/3rdparty/oscpack \
    src/3rdparty/sdl \
    src/3rdparty/tuio
HEADERS += include/qtuio.h \
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
    src/3rdparty/sdl/include/GL/glut.h \
    src/3rdparty/sdl/include/SDL.h \
    src/3rdparty/sdl/include/SDL_active.h \
    src/3rdparty/sdl/include/SDL_audio.h \
    src/3rdparty/sdl/include/SDL_byteorder.h \
    src/3rdparty/sdl/include/SDL_cdrom.h \
    src/3rdparty/sdl/include/SDL_config.h \
    src/3rdparty/sdl/include/SDL_config_minimal.h \
    src/3rdparty/sdl/include/SDL_config_win32.h \
    src/3rdparty/sdl/include/SDL_copying.h \
    src/3rdparty/sdl/include/SDL_cpuinfo.h \
    src/3rdparty/sdl/include/SDL_endian.h \
    src/3rdparty/sdl/include/SDL_error.h \
    src/3rdparty/sdl/include/SDL_events.h \
    src/3rdparty/sdl/include/SDL_getenv.h \
    src/3rdparty/sdl/include/SDL_joystick.h \
    src/3rdparty/sdl/include/SDL_keyboard.h \
    src/3rdparty/sdl/include/SDL_keysym.h \
    src/3rdparty/sdl/include/SDL_loadso.h \
    src/3rdparty/sdl/include/SDL_main.h \
    src/3rdparty/sdl/include/SDL_mouse.h \
    src/3rdparty/sdl/include/SDL_mutex.h \
    src/3rdparty/sdl/include/SDL_name.h \
    src/3rdparty/sdl/include/SDL_opengl.h \
    src/3rdparty/sdl/include/SDL_platform.h \
    src/3rdparty/sdl/include/SDL_quit.h \
    src/3rdparty/sdl/include/SDL_rwops.h \
    src/3rdparty/sdl/include/SDL_stdinc.h \
    src/3rdparty/sdl/include/SDL_syswm.h \
    src/3rdparty/sdl/include/SDL_thread.h \
    src/3rdparty/sdl/include/SDL_timer.h \
    src/3rdparty/sdl/include/SDL_types.h \
    src/3rdparty/sdl/include/SDL_version.h \
    src/3rdparty/sdl/include/SDL_video.h \
    src/3rdparty/sdl/include/begin_code.h \
    src/3rdparty/sdl/include/close_code.h \
    src/3rdparty/tuio/TuioClient.h \
    src/3rdparty/tuio/TuioContainer.h \
    src/3rdparty/tuio/TuioCursor.h \
    src/3rdparty/tuio/TuioListener.h \
    src/3rdparty/tuio/TuioObject.h \
    src/3rdparty/tuio/TuioPoint.h \
    src/3rdparty/tuio/TuioServer.h \
    src/3rdparty/tuio/TuioTime.h
SOURCES += src/main.cpp \
    src/qtuio.cpp
FORMS += qtuio.ui
RESOURCES += 

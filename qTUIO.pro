TEMPLATE = app
TARGET = qTUIO
QT += core \
    gui \
    xml \
    network \
    opengl
INCLUDEPATH += 	contrib/ \
				contrib/oscpack \
				contrib/sdl \
				contrib/tuio
HEADERS += contrib/oscpack/ip/IpEndpointName.h \
    contrib/oscpack/ip/NetworkingUtils.h \
    contrib/oscpack/ip/PacketListener.h \
    contrib/oscpack/ip/TimerListener.h \
    contrib/oscpack/ip/UdpSocket.h \
    contrib/oscpack/osc/MessageMappingOscPacketListener.h \
    contrib/oscpack/osc/OscException.h \
    contrib/oscpack/osc/OscHostEndianness.h \
    contrib/oscpack/osc/OscOutboundPacketStream.h \
    contrib/oscpack/osc/OscPacketListener.h \
    contrib/oscpack/osc/OscPrintReceivedElements.h \
    contrib/oscpack/osc/OscReceivedElements.h \
    contrib/oscpack/osc/OscTypes.h \
    contrib/sdl/include/GL/glut.h \
    contrib/sdl/include/SDL.h \
    contrib/sdl/include/SDL_active.h \
    contrib/sdl/include/SDL_audio.h \
    contrib/sdl/include/SDL_byteorder.h \
    contrib/sdl/include/SDL_cdrom.h \
    contrib/sdl/include/SDL_config.h \
    contrib/sdl/include/SDL_config_minimal.h \
    contrib/sdl/include/SDL_config_win32.h \
    contrib/sdl/include/SDL_copying.h \
    contrib/sdl/include/SDL_cpuinfo.h \
    contrib/sdl/include/SDL_endian.h \
    contrib/sdl/include/SDL_error.h \
    contrib/sdl/include/SDL_events.h \
    contrib/sdl/include/SDL_getenv.h \
    contrib/sdl/include/SDL_joystick.h \
    contrib/sdl/include/SDL_keyboard.h \
    contrib/sdl/include/SDL_keysym.h \
    contrib/sdl/include/SDL_loadso.h \
    contrib/sdl/include/SDL_main.h \
    contrib/sdl/include/SDL_mouse.h \
    contrib/sdl/include/SDL_mutex.h \
    contrib/sdl/include/SDL_name.h \
    contrib/sdl/include/SDL_opengl.h \
    contrib/sdl/include/SDL_platform.h \
    contrib/sdl/include/SDL_quit.h \
    contrib/sdl/include/SDL_rwops.h \
    contrib/sdl/include/SDL_stdinc.h \
    contrib/sdl/include/SDL_syswm.h \
    contrib/sdl/include/SDL_thread.h \
    contrib/sdl/include/SDL_timer.h \
    contrib/sdl/include/SDL_types.h \
    contrib/sdl/include/SDL_version.h \
    contrib/sdl/include/SDL_video.h \
    contrib/sdl/include/begin_code.h \
    contrib/sdl/include/close_code.h \
    contrib/tuio/TuioClient.h \
    contrib/tuio/TuioContainer.h \
    contrib/tuio/TuioCursor.h \
    contrib/tuio/TuioListener.h \
    contrib/tuio/TuioObject.h \
    contrib/tuio/TuioPoint.h \
    contrib/tuio/TuioServer.h \
    contrib/tuio/TuioTime.h \
    qtuio.h
SOURCES += main.cpp \
    qtuio.cpp
FORMS += qtuio.ui
RESOURCES += 

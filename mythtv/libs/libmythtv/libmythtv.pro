######################################################################
# Automatically generated by qmake (1.02a) Tue Jul 16 20:40:47 2002
######################################################################

TEMPLATE = lib
TARGET = mythtv
CONFIG += thread staticlib 

include ( ../../settings.pro )

INCLUDEPATH += ../libmyth ../  ../libavcodec ../libavformat ../libdvbdev
DEPENDPATH += ../libmyth ../libvbitext ../libavcodec ../libavformat ../libdvbdev

TARGETDEPS += ../libmyth/libmyth-$${LIBVERSION}.so
TARGETDEPS += ../libavcodec/libavcodec.a ../libavformat/libavformat.a
TARGETDEPS += ../libvbitext/libvbitext.a

QMAKE_CXXFLAGS_RELEASE += `freetype-config --cflags`
QMAKE_CXXFLAGS_DEBUG += `freetype-config --cflags`

# Input
HEADERS += channel.h commercial_skip.h filter.h format.h frame.h frequencies.h 
HEADERS += guidegrid.h infodialog.h infostructs.h jitterometer.h lzoconf.h 
HEADERS += minilzo.h mmx.h NuppelVideoPlayer.h NuppelVideoRecorder.h osd.h 
HEADERS += osdtypes.h programinfo.h profilegroup.h recordingprofile.h 
HEADERS += remoteencoder.h remoteutil.h RingBuffer.h scheduledrecording.h 
HEADERS += RTjpegN.h ttfont.h tv_play.h tv_rec.h videosource.h yuv2rgb.h
HEADERS += progfind.h decoderbase.h nuppeldecoder.h avformatdecoder.h
HEADERS += recorderbase.h mpegrecorder.h channelbase.h
HEADERS += vsync.h proglist.h hdtvrecorder.h fifowriter.h filtermanager.h
HEADERS += videooutbase.h videoout_xv.h videoout_null.h xbox.h
HEADERS += ivtvdecoder.h videoout_ivtv.h dbcheck.h udpnotify.h

SOURCES += channel.cpp commercial_skip.cpp frequencies.c guidegrid.cpp
SOURCES += infodialog.cpp infostructs.cpp jitterometer.cpp minilzo.cpp 
SOURCES += NuppelVideoPlayer.cpp NuppelVideoRecorder.cpp osd.cpp
SOURCES += osdtypes.cpp programinfo.cpp recordingprofile.cpp remoteencoder.cpp
SOURCES += remoteutil.cpp RingBuffer.cpp RTjpegN.cpp scheduledrecording.cpp
SOURCES += ttfont.cpp tv_play.cpp tv_rec.cpp videosource.cpp yuv2rgb.cpp
SOURCES += progfind.cpp nuppeldecoder.cpp avformatdecoder.cpp recorderbase.cpp
SOURCES += mpegrecorder.cpp channelbase.cpp filtermanager.cpp
SOURCES += vsync.c proglist.cpp hdtvrecorder.cpp videooutbase.cpp 
SOURCES += videoout_xv.cpp fifowriter.cpp videoout_null.cpp xbox.cpp
SOURCES += ivtvdecoder.cpp videoout_ivtv.cpp dbcheck.cpp profilegroup.cpp
SOURCES += udpnotify.cpp

using_xvmc {
    SOURCES += videoout_xvmc.cpp
    HEADERS += videoout_xvmc.h
    DEFINES += USING_XVMC
}

using_viahwslice {
    SOURCES += videoout_viaslice.cpp
    SOURCES += videoout_viaslice.h
    DEFINES += USING_VIASLICE
}

using_dvb {
    SOURCES += dvbrecorder.cpp dvbchannel.cpp dvbdiseqc.cpp
    HEADERS += dvbtypes.h dvbrecorder.h dvbchannel.h dvbdiseqc.h
    TARGETDEPS += ../libdvbdev/libdvbdev.a
}


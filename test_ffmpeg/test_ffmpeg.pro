TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

LIBS += C:/study/video/ffmpeg/ffmpeg-4.1.3-win32-dev/lib/avcodec.lib\
        C:/study/video/ffmpeg/ffmpeg-4.1.3-win32-dev/lib/avutil.lib\
        C:/study/video/ffmpeg/ffmpeg-4.1.3-win32-dev/lib/postproc.lib\
        C:/study/video/ffmpeg/ffmpeg-4.1.3-win32-dev/lib/swresample.lib\
        C:/study/video/ffmpeg/ffmpeg-4.1.3-win32-dev/lib/swscale.lib\
        C:/study/video/ffmpeg/ffmpeg-4.1.3-win32-dev/lib/avdevice.lib\
        C:/study/video/ffmpeg/ffmpeg-4.1.3-win32-dev/lib/avfilter.lib\
        C:/study/video/ffmpeg/ffmpeg-4.1.3-win32-dev/lib/avformat.lib\

INCLUDEPATH +=C:/study/video/ffmpeg/ffmpeg-4.1.3-win32-dev/include

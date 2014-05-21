TEMPLATE = app
TARGET = 
DEPENDPATH += . gui src src/tgl
INCLUDEPATH += . src src/tgl

CONFIG += debug
#CONFIG += release sse sse2

QMAKE_LFLAGS_RELEASE = -Wl,-O3
QMAKE_CXXFLAGS_RELEASE = -O3

OBJECTS_DIR = build
UI_DIR = src/gui
MOC_DIR = build/moc

# Input
HEADERS += src/mainwindow.h \
           src/teaplot.h \
           src/viewport.h \
           src/tgl/matrix.h \
           src/tgl/screen.h \
           src/tgl/tgl.h \
           src/tgl/vector.h \
           src/tgl/shape.h \
           src/tgl/line.h \
           src/tgl/point.h \
           src/tgl/objectparser.h \
           src/tgl/triangle.h
FORMS += gui/mainWindow.ui
SOURCES += src/main.cpp \
           src/teaplot.cpp \
           src/viewport.cpp \
           src/mainwindow.cpp \
           src/tgl/matrix.cpp \
           src/tgl/screen.cpp \
           src/tgl/tgl.cpp \
           src/tgl/vector.cpp \
           src/tgl/shape.cpp \
           src/tgl/line.cpp \
           src/tgl/point.cpp \
           src/tgl/objectparser.cpp\
           src/tgl/triangle.cpp

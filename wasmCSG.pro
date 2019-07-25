TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$(EMSDK)/fastcomp/emscripten/system/include/

SOURCES += \
        src/booleans.cpp \
        src/box3.cpp \
        src/bspnode.cpp \
        src/buffergeometry.cpp \
        src/face3.cpp \
        src/geometry.cpp \
        src/main.cpp \
        src/matrix4.cpp \
        src/meshutils.cpp \
        src/triangle.cpp \
        src/utils.cpp \
        src/vector2.cpp \
        src/vector3.cpp

HEADERS += \
        src/booleans.h \
        src/box3.h \
        src/bspnode.h \
        src/buffergeometry.h \
        src/constants.h \
        src/face3.h \
        src/geometry.h \
        src/matrix4.h \
        src/meshutils.h \
        src/triangle.h \
        src/utils.h \
        src/vector2.h \
        src/vector3.h

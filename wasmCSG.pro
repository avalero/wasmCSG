TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$(EMSDK)/fastcomp/emscripten/system/include/

SOURCES += \
        src/buffergeometry.cpp \
        src/face3.cpp \
        src/geometry.cpp \
        src/node.cpp \
        src/main.cpp \
        src/matrix4.cpp \
        src/polygon.cpp \
        src/threebsp.cpp \
        src/vector2.cpp \
        src/vector3.cpp \
        src/vertex.cpp

HEADERS += \
        src/buffergeometry.h \
        src/constants.h \
        src/face3.h \
        src/geometry.h \
        src/node.h \
        src/matrix4.h \
        src/polygon.h \
        src/threebsp.h \
        src/vector2.h \
        src/vector3.h \
        src/vertex.h

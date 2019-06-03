TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$(EMSDK)/fastcomp/emscripten/system/include/

SOURCES += \
        src/main.cpp \
        src/matrix4.cpp \
        src/polygon.cpp \
        src/vector2.cpp \
        src/vector3.cpp \
        src/vertex.cpp

HEADERS += \
        src/matrix4.h \
        src/polygon.h \
        src/vector2.h \
        src/vector3.h \
        src/vertex.h

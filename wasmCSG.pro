TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$(EMSDK)/fastcomp/emscripten/system/include/

SOURCES += \
        src/main.cpp \
        src/polygon.cpp \
        src/vector2.cpp \
        src/vector3.cpp \
        src/vertex.cpp

HEADERS += \
        src/polygon.h \
        src/vector2.h \
        src/vector3.h \
        src/vertex.h

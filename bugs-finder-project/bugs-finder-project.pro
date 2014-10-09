TEMPLATE = app
TARGET = test
VERSION = 0.1
QT += core gui quick qml

CONFIG += c++11

SOURCES += main.cpp \
    gl-engine/nodecoords.cpp \
    gl-engine/nodesize.cpp \
    gl-engine/screennode.cpp \
    gl-engine/renderthread.cpp \
    gl-engine/texturenode.cpp \
    gl-engine/renderer.cpp

RESOURCES += \
    qml/cs_qml.qrc \
    gl-engine/shaders/cs_shaders.qrc \
    images/cs_images.qrc

HEADERS += \
    gl-engine/nodecoords.h \
    gl-engine/nodesize.h \
    gl-engine/screennode.h \
    gl-engine/renderthread.h \
    gl-engine/texturenode.h \
    gl-engine/renderer.h


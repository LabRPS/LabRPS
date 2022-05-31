QMAKE_PROJECT_DEPTH = 0
linux-g++-64: libsuff=64
QT -= gui

TARGET = windlabapi
TEMPLATE = lib
DEFINES += WINDLABAPI_LIBRARY

CONFIG += c++17

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target


# Add more folders to ship with the application, here
folder_01.source = qml/GControl
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

QT+= qml quick

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    mdevice.cpp

# Installation path
# target.path =

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml \
    qml/GControl/main.qml

HEADERS += \
    mdevice.h \
    tcpcommands.h

LIBS += -L$$PWD/../../libGSocket/bin/ -lGSocket

INCLUDEPATH += $$PWD/../../libGSocket/src
DEPENDPATH += $$PWD/../../libGSocket/src

QMAKE_CXXFLAGS += -std=gnu++11

RESOURCES += \
    res.qrc

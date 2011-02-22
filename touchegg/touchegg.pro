TEMPLATE     = app
TARGET       = touchegg
QT          += core gui
OBJECTS_DIR += build
MOC_DIR     += build
LIBS        += -lutouch-geis -lX11
//DEFINES      = QT_NO_DEBUG_OUTPUT


target.path  = /usr/bin
config.path  = /usr/share/touchegg
config.files = installation/touchegg.conf
INSTALLS += target config


include(src/touchegg/touchegg.pri)

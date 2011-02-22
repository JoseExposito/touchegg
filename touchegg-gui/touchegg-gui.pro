TEMPLATE     = app
TARGET       = touchegg-gui
QT          += core gui
OBJECTS_DIR += build
MOC_DIR     += build
//DEFINES      = QT_NO_DEBUG_OUTPUT


//target.path  = /usr/bin
//config.path  = /usr/share/touchegg
//config.files = installation/touchegg.conf
//INSTALLS += target config


include(src/touchegg-gui/touchegg-gui.pri)

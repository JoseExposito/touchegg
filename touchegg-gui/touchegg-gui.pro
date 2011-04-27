TEMPLATE        = app
TARGET          = touchegg-gui
QT             += core gui xml
OBJECTS_DIR    += build
MOC_DIR        += build
RCC_DIR        += build
UI_HEADERS_DIR += build
UI_SOURCES_DIR += build
//DEFINES      = QT_NO_DEBUG_OUTPUT


target.path = /usr/bin
menu.path   = /usr/share/applications
menu.files  = installation/touchegg-gui.desktop
icon.path   = /usr/share/icons
icon.files  = installation/touchegg-gui.png
INSTALLS   += target menu icon


include(src/touchegg-gui/touchegg-gui.pri)

TEMPLATE     = app
TARGET       = touchegg
QT          += gui core xml
LIBS        += -lgeis -lX11 -lXtst -lXext
//DEFINES      = QT_NO_DEBUG_OUTPUT

target.path  = /usr/bin
config.path  = /usr/share/touchegg
config.files = installation/touchegg.conf
INSTALLS    += target config

include(src/touchegg/touchegg.pri)

OTHER_FILES += \
    documentation/doxyfile_es \
    documentation/doxyfile_en \
    README \
    COPYING \
    CHANGELOG \
    COPYRIGHT

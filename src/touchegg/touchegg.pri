include(util/util.pri)
include(config/config.pri)

include(gestures/collector/gestures.collector.pri)
include(gestures/handler/gestures.handler.pri)
include(gestures/factory/gestures.factory.pri)
include(gestures/implementation/gestures.implementation.pri)
include(gestures/types/gestures.types.pri)

include(actions/types/actions.types.pri)
include(actions/factory/actions.factory.pri)
include(actions/implementation/actions.implementation.pri)

include(windows/windows.pri)

HEADERS += \
    src/touchegg/Touchegg.h

SOURCES += src/touchegg/Main.cpp \
    src/touchegg/Touchegg.cpp

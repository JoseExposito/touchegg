include(presentation/config_forms/presentation.config_forms.pri)
include(presentation/widgets/presentation.widgets.pri)
include(presentation/main_window/presentation.main_window.pri)

include(logic/facade/logic.facade.pri)
include(logic/application_service/logic.application_service.pri)

include(data/transaction_manager/data.transaction_manager.pri)
include(data/dao/data.dao.pri)

include(resources/resources.pri)
include(util/util.pri)

SOURCES += \
    src/touchegg-gui/Main.cpp

include(presentation/config_forms/presentation.config_forms.pri)
include(presentation/widgets/presentation.widgets.pri)
include(presentation/main_window/presentation.main_window.pri)
include(presentation/gui_event/presentation.gui_event.pri)
include(presentation/gui_controller/presentation.gui_controller.pri)

include(logic/facade/logic.facade.pri)
include(logic/application_service/logic.application_service.pri)
include(logic/transfer/logic.transfer.pri)
include(logic/type/logic.type.pri)
include(logic/factory/logic.factory.pri)

include(data/transaction_manager/data.transaction_manager.pri)
include(data/dao/data.dao.pri)
include(data/factory/data.factory.pri)

include(resources/resources.pri)
include(util/util.pri)

SOURCES += \
    src/touchegg-gui/Main.cpp

qt_add_qml_module(HistoryViewComponents
    URI PhotoEditor.View.HistoryViewComponents
    VERSION 1.0
    QML_FILES
        HistoryFooter.qml
)

target_link_libraries(PhotoEditor PRIVATE Qt6::Quick)

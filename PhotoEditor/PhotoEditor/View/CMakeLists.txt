qt_add_qml_module(View
    URI PhotoEditor.View
    VERSION 1.0
    QML_FILES
        EditView.qml
        HistoryView.qml
)

target_link_libraries(PhotoEditor PRIVATE Qt6::Quick)

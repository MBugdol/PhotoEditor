qt_add_qml_module(Menu
    URI PhotoEditor.Menu
    VERSION 1.0
    QML_FILES
        PhotoMenuBar.qml
        PhotoToolBar.qml
)

target_link_libraries(PhotoEditor PRIVATE Qt6::Quick)

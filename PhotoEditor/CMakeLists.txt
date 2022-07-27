cmake_minimum_required(VERSION 3.16)

project(PhotoEditor VERSION 0.1 LANGUAGES CXX)
#set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTORCC ON)

#Qt Setup
find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)
qt_standard_project_setup()

qt_add_executable(PhotoEditor
    src/main.cpp
    src/EditedImageProvider.cpp
    src/EditedImageProvider.h
    src/PhotoEditor.cpp
    src/PhotoEditor.h
    src/PhotoEditionCommands.cpp
    src/PhotoEditionCommands.h
    src/PhotoActionData.cpp
    src/PhotoActionData.h
    qml/qml.qrc
)

qt_add_qml_module(PhotoEditor
    URI PhotoEditor
    VERSION 1.0
    QML_FILES
        qml/main.qml
        #menu
        qml/menu/PhotoMenuBar.qml
        qml/menu/PhotoToolBar.qml
        #custom elements
        qml/customElements/CombinedSlider.qml
        qml/customElements/IntegerInput.qml
        qml/customElements/PhotoDialog.qml
        qml/customElements/Section.qml
        qml/customElements/Separator.qml
        #views
        qml/view/EditView.qml
        qml/view/HistoryView.qml
        qml/view/historyViewComponents/HistoryFooter.qml
)

#check it out later
set_target_properties(PhotoEditor PROPERTIES
    WIN32_EXECUTABLE TRUE
)
target_include_directories(PhotoEditor PRIVATE &{PhotoEditor_SOURCE_DIR})
target_link_libraries(PhotoEditor
    PRIVATE Qt6::Quick)

cmake_minimum_required(VERSION 3.16)
project(PhotoEditor VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

find_package(Qt6 6.2 REQUIRED COMPONENTS Core Qml Gui Quick Widgets)

qt_standard_project_setup()

qt_add_executable(PhotoEditor WIN32
    main.cpp
    src/EditedImageProvider.cpp
    src/PhotoActionData.cpp
    src/PhotoEditionCommands.cpp
    src/PhotoEditor.cpp
)

qt_add_qml_module(PhotoEditor
    URI PhotoEditor
    VERSION 1.0
    QML_FILES
        main.qml
        qml/CustomElements/CombinedSlider.qml
        qml/CustomElements/IntegerInput.qml
        qml/CustomElements/PhotoDialog.qml
        qml/CustomElements/Section.qml
        qml/CustomElements/Separator.qml
        qml/Menu/PhotoMenuBar.qml
        qml/Menu/PhotoToolBar.qml
        qml/View/EditView.qml
        qml/View/HistoryView.qml
        qml/View/HistoryViewComponents/HistoryFooter.qml

)

target_link_libraries(PhotoEditor PRIVATE Qt6::Core Qt6::Qml Qt6::Widgets Qt6::Widgets Qt6::Gui Qt6::Quick)
set_target_properties(PhotoEditor PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

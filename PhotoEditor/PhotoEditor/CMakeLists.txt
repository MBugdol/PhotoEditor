cmake_minimum_required(VERSION 3.16)

project(PhotoEditor VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Qml Quick Gui REQUIRED)

qt_add_executable(appPhotoEditor
    main.cpp
)

qt_add_qml_module(appPhotoEditor
    URI PhotoEditor
    VERSION 1.0
    QML_FILES main.qml 
)
add_subdirectory(Backend)
add_subdirectory(CustomElements)
add_subdirectory(Menu)
add_subdirectory(View)
add_subdirectory(View/HistoryViewComponents)

set_target_properties(appPhotoEditor PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appPhotoEditor
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appPhotoEditor
    PRIVATE Qt6::Quick)

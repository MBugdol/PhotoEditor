add_executable(PhotoEditor
    EditedImageProvider.cpp
    PhotoActionData.cpp
    PhotoEditionCommands.cpp
    PhotoEditor.cpp
)

target_link_libraries(PhotoEditor PRIVATE Qt6::Quick)


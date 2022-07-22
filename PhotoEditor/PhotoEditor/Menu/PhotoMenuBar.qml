import QtQuick 2.3
import QtQuick.Controls
import QtQuick.Layouts

MenuBar {
    signal menuChoicePhotoAction(action: string)
    signal menuChoiceFile(action: string)
    signal menuChoiceView(action: string)
    //FILE MENU
    Menu {
        title: qsTr("File")
        MenuItem {
            text: qsTr("Open photo")
            onTriggered: menuChoiceFile("open")
        }
        MenuItem {
            text: qsTr("Save photo")
            onTriggered: menuChoiceFile("save")
        }
        MenuItem {
            text: qsTr("Exit")
            onTriggered: Qt.quit()
        }
    }
    //EDIT MENU
    Menu {
        title: qsTr("Edit")
        MenuItem {
            text: qsTr("Undo")
            onTriggered: editor.undo()
        }
        MenuItem {
            text: qsTr("Redo")
            onTriggered: editor.redo()
        }
    }
    //VIEW MENU
    Menu {
        title: qsTr("View")
        MenuItem {
            text: qsTr("Photo edition")
            onTriggered: menuChoiceView("edit")
        }
        MenuItem {
            text: qsTr("Action history")
            onTriggered: menuChoiceView("history")
        }
    }
    //TRANSFORM MENU
    Menu {
        title: qsTr("Transform")
        Menu {
            title: qsTr("Rotate")
            MenuItem {
                text: qsTr("90 deg. right")
                onTriggered: {editor.execute(editor.rotation(90)); editor.approveChanges()}
            }
            MenuItem {
                text: qsTr("90 deg. left")
                onTriggered: {editor.execute(editor.rotation(-90)); editor.approveChanges()}
            }
            MenuItem {
                text: qsTr("180 deg.")
                onTriggered: {editor.execute(editor.rotation(180)); editor.approveChanges()}
            }
        }
        Menu {
            title: qsTr("Flip")
            MenuItem {
                text: qsTr("Vertically")
                onTriggered: {editor.execute(editor.flip("vertical")); editor.approveChanges()}
            }
            MenuItem {
                text: qsTr("Horizontally")
                onTriggered: {editor.execute(editor.flip("horizontal")); editor.approveChanges()}
            }
        }
        //MenuItem {
        //    text: qsTr("Scale image")
        //    onTriggered: menuChoicePhotoAction("scale")
        //}
    }
    //FILTERS MENU
    Menu {
        title: qsTr("Filters")
        MenuItem {
            text: qsTr("Grayscale")
            onTriggered: {editor.execute(editor.grayscale()); editor.approveChanges()}
        }
        MenuItem {
            text: qsTr("Hue")
            onTriggered: menuChoicePhotoAction("hue")
        }
        Menu {
            title: qsTr("Reset color channel")
            MenuItem {
                text: qsTr("Red")
                onTriggered: {editor.execute(editor.resetColorChannel("red")); editor.approveChanges()}
            }
            MenuItem {
                text: qsTr("Green")
                onTriggered: {editor.execute(editor.resetColorChannel("green")); editor.approveChanges()}
            }
            MenuItem {
                text: qsTr("Blue")
                onTriggered: {editor.execute(editor.resetColorChannel("blue")); editor.approveChanges()}
            }
        }
    }
}

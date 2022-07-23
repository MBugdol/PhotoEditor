import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ToolBar {
    signal menuChoiceFile(action: string)
    RowLayout {
        ToolButton {
            text: qsTr("<")
            onClicked: editor.undo();
        }
        ToolButton {
            text: qsTr(">")
            onClicked: editor.redo();
        }
        ToolButton {
            text: qsTr("Open")
            onClicked: menuChoiceFile("open")
        }
        ToolButton {
            text: qsTr("Save")
            onClicked: menuChoiceFile("save")
        }
        ToolButton {
            text: qsTr("Export")
        }
    }
}

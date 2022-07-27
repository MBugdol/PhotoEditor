import QtQuick 2.3
import QtQuick.Layouts
import QtQuick.Controls

Loader {
    signal choice(action: string)
    id: footerLoader
    width: parent.width
    sourceComponent: idle
    states: [
        State {
            name: "idle"
            PropertyChanges {
                footerLoader {sourceComponent: idle}
            }
        },
        State {
            name: "swap"
            PropertyChanges {
                footerLoader {sourceComponent: swap}
            }
        }
    ]
    Component {
        id: idle
        ToolBar {
            id: idleToolBar
            anchors.fill: parent
            RowLayout {
                ToolButton {
                    id: removeButton
                    text: "Remove"
                    onClicked: choice("remove")
                }
                ToolButton {
                    id: swapButton
                    text: "Swap"
                    onClicked: {choice("beginSwap"); footerLoader.state = "swap"}
                }
            }
        }
    }
    Component {
        id: swap
        ToolBar {
            id: swapToolBar
            anchors.fill: parent
            RowLayout {
                ToolButton {
                    id: confirmSwapButton
                    text: "Confirm"
                    onClicked: {choice("confirmSwap"); footerLoader.state = "idle"}
                }
                ToolButton {
                    id: cancelSwapButton
                    text: "Cancel"
                    onClicked: {choice("cancelSwap"); footerLoader.state = "idle"}
                }
            }
        }
    }
}

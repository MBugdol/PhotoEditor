import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import "historyViewComponents"

ListView {
    id: listView
    anchors.fill: parent
    model: editor.history()
    state: "idle"
    property int storedIndex: -1
    Connections {target: editor; onHistoryUpdated: {model = 0; model = editor.history()}}
    states: [
        State {
            name: "idle"; when: listView.storedIndex === -1
            StateChangeScript {
                script: {
                    listView.currentIndex = listView.storedIndex
                }
            }
        },
        State {
            name: "remove"
            StateChangeScript {
                script: {
                    editor.remove(listView.currentIndex)
                }
            }
        },
        State {
            name: "beginSwap"
            StateChangeScript {
                script: {
                    listView.storedIndex = listView.currentIndex
                }
            }
        },
        State {
            name: "confirmSwap"
            StateChangeScript {
                script: {
                    editor.swap(storedIndex, listView.currentIndex)
                    listView.currentIndex = listView.storedIndex
                    listView.storedIndex = -1
                }

            }
        },
        State {
            name: "cancelSwap"
            StateChangeScript {
                script: {
                    listView.currentIndex = listView.storedIndex
                    listView.storedIndex = -1
                }
            }
        }
    ]
    delegate: Item {
        id: item
        property int index: model.index
        property string text: modelData.text
        property string action: modelData.action
        property var args: modelData.args
        property alias color: itemBox.color
        color: listView.storedIndex === -1 ? (item.ListView.isCurrentItem ? "orange" : "#535353") :
            (item.index === listView.storedIndex ? "orange" : item.ListView.isCurrentItem ? "green" : "#535353")
        width: parent.width
        height: itemBox.height + separator.height
        Rectangle {
            id: itemBox
            width: parent.width
            height: description.height + 10
            Row {
                anchors.fill: parent
                Text {
                    id: description
                    anchors.verticalCenter: parent.verticalCenter
                    width: 0.5*parent.width - textSeparator.width
                    color: "white"
                    text: item.text
                }
                Rectangle {
                    id: textSeparator
                    height: parent.height
                    color: "#737373"
                    width: 1
                }
                Text {
                    id: arguments
                    anchors.verticalCenter: parent.verticalCenter
                    width: 0.5*parent.width - textSeparator.width
                    color: "white"
                    text: ""
                    Component.onCompleted: {
                        for(var i = 0; i < item.args.length; ++i) {
                            text += item.args[i] + "; "
                        }
                    }
                }
            }
        }
        Rectangle {
            id: separator
            anchors.top: itemBox.bottom
            color: "white"
            width: parent.width
            height: 1
        }
        MouseArea {
            id: userInteraction
            anchors.fill: parent
            onClicked: {listView.currentIndex = item.index;}
        }
    }

    footer: HistoryFooter {
        id: historyFooter
        onChoice: (action) => listView.state = action
    }
}

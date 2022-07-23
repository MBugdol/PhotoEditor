import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
//import PhotoEditor //trying to fix "module "Menu" plugin "Menuplugin" not found" error
import "qml/Menu"
import "qml/View"
import "qml/CustomElements"

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Photo Editor")

    menuBar: PhotoMenuBar {id: menuBar}
    header: PhotoToolBar {id: toolBar}

    PhotoDialog {
        id: photoDialog
        onAccepted: {
            if(mode === "open") {
                originalImage.source = selectedFile
                editor.loadFromUrl(selectedFile)
            }
            else if(mode === "save") {
                editor.saveToUrl(selectedFile)
            }
        }
        Connections {target: menuBar; onMenuChoiceFile: (action) => {photoDialog.mode = action; photoDialog.open()}}
        Connections {target: toolBar; onMenuChoiceFile: (action) => {photoDialog.mode = action; photoDialog.open()}}
    }

    Item {
        id: workSpace
        anchors.fill: parent
        Separator {
            id: separatorMainRight
            color: "#424242"
            orientation: Separator.Orientations.Vertical
            startX: 3/4*parent.width
        }
        Section {
            id: sectionMain
            anchors.right: separatorMainRight.left
            Loader {
                id: mainLoader
                anchors.fill: parent
                sourceComponent: editView //change later
                states: [
                    State {
                        name: "edit"
                        PropertyChanges {
                            mainLoader {sourceComponent: editView}
                        }
                    },
                    State {
                        name: "history"
                        PropertyChanges {
                            mainLoader {sourceComponent: historyView}
                        }
                    }
                ]
                Connections {target: menuBar; onMenuChoiceView: (action) => mainLoader.state = action}
                Connections {target: menuBar; onMenuChoicePhotoAction: (action) => {mainLoader.state = "edit"}}
            }
            Component {
                id: editView
                EditView {
                    Connections {target: menuBar; onMenuChoicePhotoAction: (action) => {state = action}}
                }
            }
            Component {
                id: historyView
                HistoryView {
                }
            }
        }
        Section {
            id: sectionRight
            anchors.left: separatorMainRight.right
            Separator {
                id: separatorRightSection
                orientation: Separator.Orientations.Horizontal
                startY: 2/3 * parent.height
                color: "#424242"
            }
            Section {
                id: sectionCurrentImage
                anchors.bottom: separatorRightSection.top
                Image {
                    id: currentImage; anchors.fill: parent; source: "image://editorimg/current"; fillMode: Image.PreserveAspectFit
                    Connections {target: editorimg; onCurrentUpdated: {var src = currentImage.source; currentImage.source = ""; currentImage.source = src}}
                }
            }
            Section {
                id: sectionSmallImages
                anchors.top: separatorRightSection.bottom
                Separator {
                    id: separatorRightBottomSection
                    orientation: Separator.Orientations.Vertical
                    startX: 1/2*parent.width
                    color: "#424242"
                }
                Section {
                    id: sectionOriginalImage
                    anchors.right: separatorRightBottomSection.left
                    Image {id: originalImage; anchors.fill: parent; fillMode: Image.PreserveAspectFit}
                }
                Section {
                    id: sectionPreviewImage
                    anchors.left: separatorRightBottomSection.right
                    Image {
                        id: previewImage; anchors.fill: parent; source: "image://editorimg/preview"; fillMode: Image.PreserveAspectFit
                        Connections {target: editorimg; onPreviewUpdated: {var src = previewImage.source; previewImage.source = ""; previewImage.source = src}}
                    }
                }
            }
        }
    }
}

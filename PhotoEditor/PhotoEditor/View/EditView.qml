import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../CustomElements"

Item {
    id: editView
    anchors.fill: parent
    Loader {
        id: currentAction
        anchors.fill: parent
        sourceComponent: undefined
    }
    states: [
        State {
            name: "hue"
            PropertyChanges {
                currentAction {sourceComponent: editHue}
            }
        },
        State {
            name: "scale"
            PropertyChanges {
                currentAction {sourceComponent: editScale}
            }
        }
    ]
    Component {
        id: editHue
        ColumnLayout {
            Label {id: hueTitleLabel; text: "Adjusts each of image's pixels' hue by given value (pixel hue += given value)"}
            RowLayout {
                Label {id: hueLabel; text: "Hue"}
                CombinedSlider {id: hueSlider; minval: -180; maxval: 180; step: 1; onValueChanged: previewUpdate.restart(); Layout.alignment: Qt.AlignLeft}
            }
            Button {text: "Adjust hue"; onClicked: editor.approveChanges();Layout.alignment: Qt.AlignRight}
            Timer {
                id: previewUpdate
                interval: 250
                onTriggered: {editor.execute(editor.hueShift(hueSlider.value))}
            }
        }
    }
    Component {
        id: editScale
        Frame {
            id: adjustScale
            function scale() {editor.execute(editor.scale(scaleWidthInput.text, scaleHeightInput.text))}//scaleHeightInput.text))}
            anchors.fill: parent
            ColumnLayout {
                Label {id: scaleTitleLabel; text: "Scales the image to given size"}
                GridLayout {
                    columns: 2
                    Label {id: scaleWidthLabel; text: "Width"}
                    IntegerInput {id: scaleWidthInput; minval: 1; maxval: 3840; startval: 1920;}
                    Label {id: scaleHeightLabel; text: "Height"}
                    IntegerInput {id: scaleHeightInput; minval: 1; maxval: 3840; startval: 1080;}
                }
                Button {
                    text: "Apply"; onClicked: {adjustScale.scale();editor.approveChanges()} Layout.alignment: Qt.AlignRight
                }
            }
        }
    }
}

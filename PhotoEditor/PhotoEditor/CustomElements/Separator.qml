import QtQuick 2.3
import QtQuick.Controls

Rectangle {
    id: separator
    enum Orientations {
        Vertical,
        Horizontal
    }
    required property int orientation
    property alias startX: separator.x
    property alias startY: separator.y
    property int sectionWidth: parent.width
    property int sectionHeight: parent.height
    startX: 0
    startY: 0

    width: orientation === Separator.Orientations.Vertical ? 5 : sectionWidth
    height: orientation === Separator.Orientations.Horizontal ? 5 : sectionHeight

    MouseArea {
        anchors.fill: parent
        cursorShape: parent.orientation === Separator.Orientations.Vertical ? Qt.SizeHorCursor : Qt.SizeVerCursor
        drag.target: parent
        drag.axis: parent.orientation === Separator.Orientations.Vertical ? Drag.XAxis : Drag.YAxis
        drag.minimumX: 0
        drag.maximumX: sectionWidth - separator.width
        drag.minimumY: 0
        drag.maximumY: sectionHeight - separator.height
    }
}

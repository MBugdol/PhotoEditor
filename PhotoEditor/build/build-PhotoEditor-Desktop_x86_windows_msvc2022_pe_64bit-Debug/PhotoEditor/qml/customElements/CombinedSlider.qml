import QtQuick 2.3
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    property int minval: 0
    property int maxval: 10
    property int step: 1
    property alias value: slider.value
    spacing: 10
    Slider {
        id: slider
        from: minval
        to: maxval
        stepSize: 1
        onMoved: input.text = value
    }
    TextField {
        id: input
        validator: IntValidator{}
        onEditingFinished: {text < minval ? text = minval : text > maxval ? text = maxval : text = text; slider.value = text}
    }
}

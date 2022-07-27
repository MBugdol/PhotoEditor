import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

TextField {
    property int minval: 0
    property int maxval: inf
    property int startval: 0
    text: startval
    validator: IntValidator {}
    onEditingFinished: text = text < minval ? minval : text > maxval ? maxval : text
}

import QtQuick 2.3
import QtQuick.Dialogs

FileDialog {
    property string mode;
    nameFilters: ["Image files (*.jpg, *.png)", "All files (*)"]
    defaultSuffix: ".png"
    title: mode === "open" ? "Choose an image file" : mode === "save" ? "Choose a location and name to save the file to" : "This dialog shouldn't exist"
    fileMode: mode === "open" ? FileDialog.OpenFile : mode === "save" ? FileDialog.SaveFile : FileDialog.OpenFile
}

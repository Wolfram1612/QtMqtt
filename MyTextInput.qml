import QtQuick 2.15
import QtQuick.Layouts 1.15

TextInput {
    width: 10
    font.pixelSize: 24
    font.italic: true
    color: "darkred"
    selectByMouse: true
    Layout.maximumWidth: 500
    Layout.fillWidth: true
    clip: true

    Rectangle {
        width: parent.width
        anchors.bottom: parent.bottom
        height: 1
        color: "black"
    }
}

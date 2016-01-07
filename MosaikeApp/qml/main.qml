﻿import QtQuick 2.0
import QtQuick.Controls 1.3

Rectangle {
    id: rootItem
    width: 320
    height: 240
    color: "gray"

    signal openImage()

    Column {
        id: column1
        x: 55
        width: 200
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        Button {
            id: button1
            height: 32
            text: qsTr("Open Image")
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            isDefault: false
        }
    }

    Connections {
        target: button1
        onClicked: rootItem.openImage()
    }
}

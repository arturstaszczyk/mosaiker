import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2

Rectangle {
    id: rootItem
    width: 320
    height: 240
    color: "gray"

    signal openImage()

    Connections {
        target: button1
        onClicked: rootItem.openImage()
    }

    Column {
        id: column1
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: column2.left
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        Layout.alignment: Qt.AlignRight | Qt.AlignTop

        Image {
            id: image1
            width: parent.width
            height: parent.height
            source: ""
            cache: false
            function reload()
            {
                source = "";
                source = "image://imageModel/original";
            }
        }

    }

    Column {
        id: column2
        x: 0
        width: 200
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0

        Button {
            id: button1
            width: parent.width
            height: 64
            text: qsTr("Open Image")
            isDefault: false
        }
    }

    Connections
    {
        target: imageModel
        onImageUpdated: image1.reload()
    }



}


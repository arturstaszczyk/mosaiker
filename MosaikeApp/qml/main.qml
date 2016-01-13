import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2

Rectangle {
    id: rootItem
    width: 320
    height: 240
    color: "gray"
    property alias label1: label1

    signal openImage()
    signal setResourcesPath()

    Connections {
        target: imageModel
        onImageUpdated: imgOriginal.reload()
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
            id: imgOriginal
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
        x: 120
        width: 200
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0

        Button {
            id: btnOpenImage
            width: parent.width
            height: 43
            text: qsTr("Open Image")

            onClicked: rootItem.openImage()
        }

        Row {
            id: row1
            y: 0
            width: parent.width
            height: 400


            Text {
                id: label1
                x: 40
                y: 0
                width: parent.width - btnSetResourcePath.width
                height: 43

                elide: Text.ElideLeft
                color: "#090e6d"
                text: resourcesDirModel.resourcesDir
                clip: true
                wrapMode: Text.NoWrap
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignRight
                font.family: "Courier"
            }

            Button {
                id: btnSetResourcePath
                x: 5
                width: 43
                height: 43
                text: qsTr("...")

                onClicked: rootItem.setResourcesPath()
            }

        }
    }

}


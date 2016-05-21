import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2
import QtQuick.Extras 1.4

Rectangle {
    id: rootItem
    width: 640
    height: 480
    color: "gray"
    property alias label1: label1

    signal openImage()
    signal setResourcesPath()
    signal buildIndex();
    signal makeMosaic();

    Connections {
        target: mainImageModel
        onImageUpdated: imgOriginal.reload()
    }

    Column {
        id: column1
        anchors.margins: 0

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: column2.left
        anchors.left: parent.left
        Layout.alignment: Qt.AlignRight | Qt.AlignTop

        Item {
            id: imageContainer
            width: parent.width
            height: parent.height

            Image {
                id: imgOriginal
                anchors.centerIn: parent
                width: mainImageModel.size.width
                height: mainImageModel.size.height
                sourceSize.width: imageContainer.width;
                sourceSize.height: imageContainer.height;
                source: ""
                cache: false

                function reload()
                {
                    source = "";
                    source = "image://mainImageModel/original";
                }
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

        Button {
            id: btnMakeMosaic
            width: parent.width
            height: 43
            text: qsTr("Make mosaic")

            enabled: mainImageModel.loaded && btnBuildIndex.enabled
            onClicked: rootItem.makeMosaic()
        }

        GroupBox {
            id: groupBox1
            width: parent.width
            height:200
            title: qsTr("Resources index")


            Button {
                id: btnBuildIndex
                height: 43

                text: resourcesDirModel.isIndexBuilt ? "Rebuild index" : "Index not found (build)"
                isDefault: false
                anchors.top: btnSetResourcePath.bottom
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0
                enabled: resourcesDirModel.resourcesDir != "" && !resourcesDirModel.isIndexBuilding

                onClicked: rootItem.buildIndex();
            }

            Text {
                id: label1
                height: 24

                elide: Text.ElideLeft
                color: "#090e6d"
                text: resourcesDirModel.resourcesDir
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0
                clip: true
                wrapMode: Text.NoWrap
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignRight
                font.family: "Courier"
            }

            Button {
                id: btnSetResourcePath
                height: 43
                text: qsTr("Change path")
                anchors.top: label1.bottom
                anchors.topMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                enabled: !resourcesDirModel.isIndexBuilding

                onClicked: rootItem.setResourcesPath()
            }

            ProgressBar {
                id: progressBar
                x: 0
                y: 44
                width: parent.width
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0

                minimumValue: 0
                maximumValue: progressBarModel.maxValue
                value: progressBarModel.value
            }
        }

    }

}


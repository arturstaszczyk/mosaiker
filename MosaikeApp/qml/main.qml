import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2
import QtQuick.Extras 1.4
import QtGraphicalEffects 1.0

Rectangle {
    id: rootItem
    width: 640
    height: 480
    color: "gray"

    signal openImage()
    signal setResourcesPath()
    signal buildIndex();
    signal makeMosaic();

    Connections {
        target: mainImageModel
        onImageUpdated: imgOriginal.reload()
    }

    Item {
        id: statusBar
        height: 32
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        Rectangle {
            Rectangle {
                color: "black"
                height: 1
                anchors {
                    top: parent.top
                    left: parent.left
                    right: parent.right
                }
            }

            anchors.fill: parent
            color: "light gray"
        }

        Text {
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            anchors.fill: parent

            color: "#333333"
            textFormat: Text.PlainText
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft

            text: "Resources directory: " + resourcesDirModel.resourcesDir
        }
    }

    Column {
        id: leftColumn
        anchors.bottomMargin: 0
        anchors.margins: 0

        anchors.top: parent.top
        anchors.bottom: statusBar.top
        anchors.right: rightColumn.left
        anchors.left: parent.left
        Layout.alignment: Qt.AlignRight | Qt.AlignTop

        Rectangle {
            id: imageContainer
            color: "green"
            width: parent.width
            height: parent.height

            Image {
                id: imgOriginal
                anchors.centerIn: parent
                width: mainImageModel.qmlSize.width
                height: mainImageModel.qmlSize.height
                sourceSize.width: imageContainer.width;
                sourceSize.height: imageContainer.height;
                source: ""
                cache: false

                function reload()
                {
                    source = "";

                    if(mainImageModel.displayImageLoaded && mainImageModel.overlayImageLoaded)
                        source = "image://mainImageModel/compositionImage";
                    else if(mainImageModel.displayImageLoaded)
                        source = "image://mainImageModel/displayImage";
                }
            }

//            Image {
//                id: imgCreated
//                anchors.centerIn: parent
//                width: imgOriginal.width
//                height: imgOriginal.height

//                source: ""
//                cache: false

//                function reload()
//                {
//                    source = ""
//                    source = "image://secondaryImageModel/image"
//                }
//            }

//            Blend
//            {
//                anchors.fill: imgOriginal
//                source: imgOriginal
//                foregroundSource: imgCreated
//                mode: "average"
//                cached: false
//            }
        }
    }

    GroupBox {
        id: rightColumn
        title: qsTr("Make your mosaic:")

        width: 200

        anchors {
            margins: 0

            top: parent.top
            bottom: statusBar.top
            right: parent.right
        }

        Column
        {
            id: controlColumn
            anchors.fill: parent

            Text {
                id: instructionOpenImage
                width: parent.width
                text: "First, open your image:"
            }

            Button {
                id: btnOpenImage

                width: parent.width
                height: 43

                text: "Open image"

                onClicked: rootItem.openImage()

            }

            Text {
                id: instructionOpenResources
                width: parent.width
                text: "Show me your resources:"
            }

            Button {
                id: btnOpenResources
                width: parent.width
                height: 43
                text: qsTr("Set resources directory")
                enabled: !resourcesDirModel.isIndexBuilding

                onClicked: rootItem.setResourcesPath()
            }

            Text {
                id: instructionBuildIndex
                width: parent.width
                wrapMode: Text.Wrap
                text: "Preproces resources (no image will be modified):"
            }

            Button {
                id: btnBuildIndex
                width: parent.width
                height: 43

                text: resourcesDirModel.isIndexBuilt ? "Rebuild index" : "Index not found (build)"
                isDefault: false
                enabled: resourcesDirModel.resourcesDir != "" && !resourcesDirModel.isIndexBuilding

                onClicked: rootItem.buildIndex();
            }

            Text {
                id: instructionMakeMosaic
                width: parent.width
                text: "And finally build your mosaic:"
            }

            Button {
                id: btnMakeMosaic
                width: parent.width
                height: 43
                text: qsTr("Make mosaic")

                enabled: mainImageModel.displayImageLoaded && btnBuildIndex.enabled && !makeMosaicButtonModel.isBeingCreated
                onClicked: rootItem.makeMosaic()
            }

            Text {
                id: instructionProgress
                text: "Operation progress:"
            }

            ProgressBar {
                id: progressBar
                x: 0
                y: 44
                width: parent.width

                minimumValue: 0
                maximumValue: 100
                value: progressBarModel.value
            }
        }

    }


}


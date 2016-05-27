﻿import QtQuick 2.0
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
    signal saveMosaic();
    signal opacityChanged(var opacityValue);

    Connections {
        target: mainImageModel
        onComposedImageUpdated: imgOriginal.reload()
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

        Item {
            id: imageContainer
            //color: "green"
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
                width: parent.width
                wrapMode: Text.Wrap
                text: "Select match algorithm:"
            }

            ComboBox {
                id: cmbMatcher
                width: parent.width

                enabled: btnMakeMosaic.enabled
                currentIndex: 1

                model: ["Greedy matcher", "Distance matcher"]
            }

            Text {
                width: parent.width

                text: "Matcher params:"
            }

            SpinBox {
                id: spinDistance
                width: parent.width

                height: cmbMatcher.currentIndex != 0 ? 24 : 0
                enabled: cmbMatcher.currentIndex != 0 && btnMakeMosaic.enabled

                minimumValue: 0
                stepSize: 1
                value: 5
            }

            Text {
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
                text: "Operation progress:"
            }

            ProgressBar {
                id: progressBar
                width: parent.width

                minimumValue: 0
                maximumValue: 100
                value: progressBarModel.value
            }

            Text {
                text: "Adjust opacity:"
            }

            Slider {
                id: opacitySlider
                objectName: "opacitySlider"
                enabled: makeMosaicButtonModel.wasCreated

                minimumValue: 0
                maximumValue: 1
                value: 0.2
                stepSize: 0.05
                width: parent.width

                onValueChanged: rootItem.opacityChanged(value)
            }

            Text {
                text: "Save your image:"
            }

            Button {
                id: btnSave

                width: parent.width
                height: 43
                text: qsTr("Save mosaic")

                enabled: makeMosaicButtonModel.wasCreated
                onClicked: rootItem.saveMosaic()
            }
        }
    }
}


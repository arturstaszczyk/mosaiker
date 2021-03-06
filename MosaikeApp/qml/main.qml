﻿import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2
import QtQuick.Extras 1.4
import QtGraphicalEffects 1.0
import Matchers 1.0

Rectangle {
    id: rootItem
    width: 640
    height: 500
    color: "gray"

    property int buttonHeight: 32

    signal openImage()
    signal setResourcesPath()
    signal buildIndex();
    signal makeMosaic();
    signal saveMosaic();

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

    Rectangle {
        id: rightColumn
        width: 200
        color: "light gray"
        clip: true

        anchors {
            margins: 0

            top: parent.top
            bottom: statusBar.top
            right: parent.right
        }

        Column
        {
            id: controlColumn
            anchors {

                top: parent.top
                left: parent.left
                right: parent.right
                bottom: instructionProgress.top

                margins: 10
            }

            Text {
                width: parent.width
                text: "First, open your image:"
            }

            Button {
                id: btnOpenImage
                width: parent.width
                text: "Open image"

                onClicked: rootItem.openImage()
            }

            ResourcesDirControl {
                id: gbResourcesDirControl
                width: parent.width
                anchors.topMargin: 10

                onOpenResourcesButton: rootItem.setResourcesPath()
                onBuildResourcesButton: rootItem.buildIndex()
            }

            MosaicControl {
                id: gbMosaicControl
                width: parent.width
                anchors.topMargin: 10

                onMakeMosaicButton: rootItem.makeMosaic()
            }

            Text {
                text: "Adjust opacity:"
            }

            Slider {
                id: opacitySlider
                width: parent.width
                enabled: makeMosaicButtonModel.wasCreated

                minimumValue: 0
                maximumValue: 1
                stepSize: 0.05

                value: mainImageModel.opacity
                onValueChanged: mainImageModel.setOpacity(value)
            }

            Text {
                text: "Save your image:"
            }

            Button {
                id: btnSave

                width: parent.width
                height: rootItem.buttonHeight
                text: qsTr("Save mosaic")

                enabled: makeMosaicButtonModel.wasCreated
                onClicked: rootItem.saveMosaic()
            }
        }

        Text {
            id: instructionProgress
            text: "Operation progress:"

            anchors {
                bottom: progressBar.top
                left: parent.left
                right: parent.right
                topMargin: 10
                leftMargin: 10
                rightMargin: 10
            }
        }

        ProgressBar {
            id: progressBar

            anchors {
                bottom: parent.bottom
                left: parent.left
                right: parent.right
                leftMargin: 10
                rightMargin: 10
                bottomMargin: 10
            }

            minimumValue: 0
            maximumValue: 100
            value: progressBarModel.value
        }
    }
}


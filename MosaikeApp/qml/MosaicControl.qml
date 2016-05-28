import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2
import QtQuick.Extras 1.4
import QtGraphicalEffects 1.0
import Matchers 1.0

GroupBox {
    id: gbMosaicControl
    title: "Customize mosaic:"

    signal makeMosaicButton()

    Text {
        id: instructionSliceSize
        text: "Slice size:"

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
    }

    SpinBox {
        id: spinSliceSize

        anchors {
            top: instructionSliceSize.bottom
            left: parent.left
            right: parent.right
        }

        enabled: btnMakeMosaic.enabled
        minimumValue: 16
        maximumValue: 256
        stepSize: 16

        value: sliceSizeModel.sliceSize
        onValueChanged: sliceSizeModel.setSliceSize(value)
    }

    Text {
        id: instructionMatcherType

        anchors {
            top: spinSliceSize.bottom
            left: parent.left
            right: parent.right

            topMargin: 10
        }

        wrapMode: Text.Wrap
        text: "Select matcher type:"
    }

    ComboBox {
        id: cmbMatcher

        anchors {
            top: instructionMatcherType.bottom
            left: parent.left
            right: parent.right
        }

        enabled: btnMakeMosaic.enabled
        currentIndex: 1

        model: ListModel
        {
            id: cmbMatcherItems
            ListElement { text: "Greedy matcher"; matcher: Matchers.MatcherGreedy; }
            ListElement { text : "Distance matcher"; matcher: Matchers.MatcherDistance; }
        }

        onCurrentIndexChanged: matcherModel.setMatcher(cmbMatcherItems.get(cmbMatcher.currentIndex).matcher)

    }

    Text {
        id: instructionParams
        anchors {
            top: cmbMatcher.bottom
            left: parent.left
            right: parent.right
            topMargin: cmbMatcher.currentIndex != 0 ? 10 : 0
        }

        height: cmbMatcher.currentIndex != 0 ? 18 : 0
        opacity: cmbMatcher.currentIndex != 0 ? 1 : 0
        text: "Matcher params:"
    }

    SpinBox {
        id: spinDistance
        anchors {
            top: instructionParams.bottom
            left: parent.left
            right: parent.right
        }

        height: cmbMatcher.currentIndex != 0 ? 24 : 0
        opacity: cmbMatcher.currentIndex != 0 ? 1 : 0

        enabled: cmbMatcher.currentIndex != 0 && btnMakeMosaic.enabled

        minimumValue: 1
        stepSize: 1

        value: matcherModel.distance
        onValueChanged: matcherModel.setDistance(value)
    }

    Text {
        id: instructionBuild
        anchors {
            top: spinDistance.bottom
            left: parent.left
            right: parent.right
            topMargin: 10
        }

        text: "And finally build your mosaic:"
    }

    Button {
        id: btnMakeMosaic
        anchors {
            top: instructionBuild.bottom
            left: parent.left
            right: parent.right
        }

        text: "Make mosaic"

        enabled: mainImageModel.displayImageLoaded &&
                 resourcesDirModel.isIndexBuilt &&
                 !resourcesDirModel.isIndexBuilding &&
                 !makeMosaicButtonModel.isBeingCreated

        onClicked: gbMosaicControl.makeMosaicButton()
    }
}

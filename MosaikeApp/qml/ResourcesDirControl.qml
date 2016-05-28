import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2
import QtQuick.Extras 1.4
import QtGraphicalEffects 1.0
import Matchers 1.0

GroupBox {
    id: gbResourcesDirControl
    title: "Select resources for mosaic:"

    signal openResourcesButton()
    signal buildResourcesButton()

    Text {
        id: instructionOpenResourcesDir
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right

            margins: 0
        }

        text: "Show me your resources:"
    }

    Button {
        id: btnOpenResources

        anchors {
            top: instructionOpenResourcesDir.bottom
            left: parent.left
            right: parent.right

            margins: 0
        }

        text: "Set resources directory"
        enabled: !resourcesDirModel.isIndexBuilding

        onClicked: gbResourcesDirControl.openResourcesButton()
    }

    Text {
        id: instructionBuildIndex
        anchors {
            top: btnOpenResources.bottom
            left: parent.left
            right: parent.right

            margins: 0
            topMargin: 15
        }

        wrapMode: Text.Wrap
        text: "Preproces resources (no image will be modified):"
    }

    Button {
        id: btnBuildIndex

        anchors {
            top: instructionBuildIndex.bottom
            left: parent.left
            right: parent.right

            margins: 0
        }

        text: resourcesDirModel.isIndexBuilt ? "Rebuild index" : "Index not found (build)"
        enabled: resourcesDirModel.resourcesDir != "" && !resourcesDirModel.isIndexBuilding

        onClicked: gbResourcesDirControl.buildResourcesButton();
    }
}

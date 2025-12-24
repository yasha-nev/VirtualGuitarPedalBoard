import QtQuick

Item {
    id: uiBasePedal

    property string pedalName: "base Pedal"

    property string pedalColor: "#555555"

    property QtObject object

    property bool isActive: false

    signal pedalClicked()

    Connections {
        target: object
        onIsActiveChanged: function(active) {
            uiBasePedal.isActive = active
        }
}

    width: 120
    height: 180

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            uiBasePedal.pedalClicked()
        }
    }

    Rectangle {
        anchors.centerIn: parent
        anchors.fill: parent
        width: parent.width
        height: parent.height
        color: pedalColor
        border.color: "#888888"
        radius: 5

        Text {
            anchors.margins: 10
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter

            text: pedalName
            color: "white"
            font.bold: true
        }
    }

    Rectangle {
        anchors.margins: 10
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        width: 5
        height: 5
        radius: width / 2
        color: {
            if (uiBasePedal.isActive){
                return "#FFFFFF"
            } else {
                return "#000000"
            }
        }
    }
}

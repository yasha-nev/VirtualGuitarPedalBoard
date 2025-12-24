import QtQuick
import Pedals

UIBasePedal{
    id: distortion

    pedalName: "Distortion"
    pedalColor: "#AA5555"

    object: uiDistortionPedal

    onPedalClicked: {
        uiDistortionPedal.click()
    }

    UIDistortionPedal {
        id: uiDistortionPedal
    }

    Column {
        anchors.centerIn: parent
        spacing: 10

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10

            CircleSwitch {
                id: switch1
                name: "T"

                onValueChanged: (value) => uiDistortionPedal.setTone(value)
            }

            CircleSwitch {
                id: switch2
                name: "D"

                onValueChanged: (value) => uiDistortionPedal.setDist(value)
            }
        }

        CircleSwitch {
            id: switch3
            anchors.horizontalCenter: parent.horizontalCenter
            name: "L"

            onValueChanged: (value) => uiDistortionPedal.setLevel(value)
        }
    }
}

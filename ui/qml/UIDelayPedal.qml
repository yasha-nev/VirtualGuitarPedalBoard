import QtQuick
import Pedals

UIBasePedal{
    id: delay

    pedalName: "Delay"
    pedalColor: "#5555AA"

    object: uiDelayPedal

    onPedalClicked: {
        uiDelayPedal.click()
    }

    UIDelayPedal {
        id: uiDelayPedal
    }

    Column {
        anchors.centerIn: parent
        spacing: 10

        Row{
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10

            CircleSwitch{
                id: switch1
                name: "L"

                onValueChanged: (value) => uiDelayPedal.setLevel(value)
            }

            CircleSwitch{
                id: switch2
                name: "T"

                onValueChanged: (value) => uiDelayPedal.setTime(value)
            }
        }

        CircleSwitch{
            id: switch3
            anchors.horizontalCenter: parent.horizontalCenter
            name: "F"

            onValueChanged: (value) => uiDelayPedal.setFeedback(value)
        }
    }
}

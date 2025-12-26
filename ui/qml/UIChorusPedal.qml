import QtQuick
import Pedals

UIBasePedal{
    pedalName: "Chorus"
    pedalColor: "#5555FF"

    object: uiChorusPedal

    onPedalClicked: {
        uiChorusPedal.click()
    }

    UIChorusPedal {
        id: uiChorusPedal
    }

    Row{
        anchors.centerIn: parent
        spacing: 10

        CircleSwitch{
            id: switch1
            name: "R"

            onValueChanged: (value) => uiChorusPedal.setRate(value)
        }

        CircleSwitch{
            id: switch2
            name: "D"

            onValueChanged: (value) => uiChorusPedal.setDepth(value)
        }
    }
}

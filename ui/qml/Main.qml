import QtQuick
import QtQuick.Controls 2.15
import Pedals 1.0

import "js/componentCreation.js" as PedalCreator

Window {
    width: 1180
    height: 300
    visible: true
    title: qsTr("VirtualGuitarProcessor")

    Rectangle {
        anchors.fill: parent
        color: "#2a2a2a"

        Row {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 30

            Column {
                width: 160
                spacing: 20

                ComboBox {
                    id: inputDeviceComboBox
                    width: parent.width
                    model: app.inputDeviceList
                    currentIndex: 0
                    font.pointSize: 14
                    onActivated: app.setInputDevice(currentText)
                }

                ComboBox {
                    id: outputDeviceComboBox
                    width: parent.width
                    model: app.outputDeviceList
                    currentIndex: 0
                    font.pointSize: 14
                    onActivated: app.setOutputDevice(currentText)
                }

                Rectangle {
                    id: startButton
                    anchors.horizontalCenter: parent.horizontalCenter

                    width: 60
                    height: 60
                    radius: width / 2

                    property bool isActive: false
                    color: isActive ? "#FF5555" : "#555555"
                    border.color: "#888888"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            startButton.isActive ? app.stop() : app.start()
                            startButton.isActive = !startButton.isActive
                        }
                    }
                }
            }

            Rectangle {
                width: 900
                height: 260
                radius: 10
                color: "#333333"
                border.color: "#555555"

                Row {
                    id: pedalRow
                    anchors.centerIn: parent
                    spacing: 30

                    Component.onCompleted: PedalCreator.initPedals()

                    Repeater {
                        model: 5

                        delegate: Rectangle {
                            id: pedalArea

                            property QtObject pedal

                            color: "#333333"
                            width: 120
                            height: 225

                            Rectangle {
                                width: 120
                                height: 180
                                radius: 5
                                color: "#555555"
                                border.color: "#888888"

                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        pedalDialog.open()
                                        pedalDialog.index = index
                                        pedalDialog.currentTarget = parent
                                    }
                                }

                                function createPedal(pedalType, parent, pedalIndex) {
                                    var pedal = PedalCreator.createPedalObjects(pedalType, parent, pedalIndex)
                                    pedalArea.pedal = pedal
                                    app.addPedal(pedal.object, index);
                                }
                            }

                            Rectangle {
                                id: deleteButton

                                anchors.bottom: parent.bottom
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.margins: 10

                                width: 25
                                height: 25
                                radius: deleteButton.width / 2

                                color: "#555555"
                                border.color: "#888888"

                                Text {
                                    anchors.centerIn: parent
                                    text: "x"
                                    color: "#FFFFFF"
                                }

                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        PedalCreator.deletePedal(index)
                                        app.deletePedal(index)
                                    }
                                }
                            }

                            Dialog {
                                id: pedalDialog
                                title: "Choose type"

                                width: 120
                                height: 180

                                property var currentTarget: null
                                property int index: 0

                                contentItem: Item {
                                    anchors.fill: parent

                                    Column {
                                        spacing: 15
                                        anchors.centerIn: parent

                                        Button {
                                            text: "Distortion"
                                            onClicked: {
                                                pedalDialog.currentTarget.createPedal(
                                                    "Distortion",
                                                    pedalDialog.currentTarget,
                                                    pedalDialog.index
                                                )
                                                pedalDialog.close()
                                            }
                                        }

                                        Button {
                                            text: "Delay"
                                            onClicked: {
                                                pedalDialog.currentTarget.createPedal(
                                                    "Delay",
                                                    pedalDialog.currentTarget,
                                                    pedalDialog.index
                                                )
                                                pedalDialog.close()
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

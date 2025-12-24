import QtQuick
import QtQuick.Controls 2.15
import Pedals 1.0

import "js/componentCreation.js" as PedalCreator

Window {
    width: 900
    height: 600
    visible: true
    title: qsTr("VirtualGuitarProcessor")

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#2a2a2a"

        Column {
            anchors.centerIn: parent
            spacing: 20

            Row {
                spacing: 20

                ComboBox {
                    id: inputDeviceComboBox
                    width: 400
                    model: app.inputDeviceList
                    currentIndex: 0
                    onActivated: {
                        app.setInputDevice(inputDeviceComboBox.currentText)
                    }
                    font.pointSize: 14
                }

                ComboBox {
                    id: outputDeviceComboBox
                    width: 400
                    model: app.outputDeviceList
                    currentIndex: 0
                    onActivated: {
                        app.setOutputDevice(outputDeviceComboBox.currentText)
                    }
                    font.pointSize: 14
                }
            }
            Row{
                spacing: 20

                Button {
                    id: startButton
                    property bool isActive: false

                    text: "Запустить"
                    width: 400
                    height: 50
                    font.pointSize: 16

                    background: Rectangle {
                        width: 400
                        height: 50
                        radius: 5
                        color: startButton.isActive ? "#AA5555" : "#5F5F5F"
                    }

                    onClicked: {
                        app.start()
                        startButton.isActive = true
                    }
                }

                Button {
                    text: "Остановить"
                    width: 400
                    height: 50
                    font.pointSize: 16

                    background: Rectangle {
                        width: 400
                        height: 50
                        radius: 5
                        color: "#5F5F5F"
                    }


                    onClicked: {
                        app.stop()
                        startButton.isActive = false
                    }
                }
            }

            Rectangle {
                width: parent.width
                height: 250
                color: "#333333"
                border.color: "#555555"
                radius: 10
                anchors.horizontalCenter: parent.horizontalCenter

                Row {
                    id: pedalRow
                    spacing: 25
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter

                    Component.onCompleted: {
                        PedalCreator.initPedals()
                    }

                    Repeater {
                        id: repeater
                        model: 5

                        delegate: Rectangle {

                            id: pedalArea

                            property QtObject pedal

                            color: "#333333"
                            width: 120
                            height: 225

                            Rectangle {
                                anchors.top: parent.top
                                anchors.right: parent.right

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

                                function createPedal(pedalType, parent, pedalIndex){
                                    var pedal = PedalCreator.createPedalObjects(pedalType, parent, pedalIndex)
                                    pedalArea.pedal = pedal
                                    app.addPedal(pedal.object, index);
                                }
                            }

                            Rectangle {
                                id: cancelButton

                                anchors.bottom: parent.bottom
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.margins: 10

                                width: 25
                                height: 25
                                radius: cancelButton.width / 2
                                color: "#555555"
                                border.color: "#888888"

                                Text {
                                    anchors.centerIn: parent
                                    color: "#FFFFFF"
                                    text: "x"
                                }

                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        PedalCreator.deletePedal(index)
                                        app.deletePedal(index)
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Dialog {
                id: pedalDialog
                title: "Choose type"
                visible: false

                property var currentTarget: null
                property int index: 0
                property var targetId: null

                contentItem: Item {
                    width: parent.width
                    height: 100

                    Column {
                        spacing: 15
                        anchors.centerIn: parent

                        Button {
                            width: 100
                            text: "Distortion"
                            onClicked: {
                                pedalDialog.currentTarget.createPedal("Distortion", pedalDialog.currentTarget, pedalDialog.index)
                                pedalDialog.close()
                            }
                        }
                    }
                }
            }
        }
    }
}

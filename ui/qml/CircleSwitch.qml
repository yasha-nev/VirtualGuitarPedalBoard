import QtQuick

Item {
    id: circle

    width: switchWidth
    height: switchWidth

    property int switchWidth: 45
    property int circleWidth: 10
    property string name: "D"

    signal valueChanged(value: real)

    Rectangle {
        anchors.fill: parent
        width: switchWidth
        height: switchWidth
        radius: width / 2
        color: "#000000"

        Rectangle {
            id: knob
            width: circleWidth
            height: circleWidth
            radius: 15
            color: "#D7DBDD" //"#FFFFFF"
            x: (circle.width - knob.width) / 2
            y: circle.width - knob.width
        }

        MouseArea {
            id: rotateArea
            anchors.fill: parent
            onReleased: {
                knob.rotation = knob.rotation % 360
            }
            onPositionChanged: {
                var angle = Math.atan2(mouseY - circle.height / 2, mouseX - circle.width / 2) * 180 / Math.PI;
                knob.rotation = angle

                var param = angle - 90
                if (param < 0){
                    param = param + 360
                }
                circle.valueChanged(param)

                var radius = circle.width / 2 - knob.width / 2;
                var x = circle.width / 2 + radius * Math.cos(angle * Math.PI / 180);
                var y = circle.height / 2 + radius * Math.sin(angle * Math.PI / 180);

                knob.x = x - knob.width / 2;
                knob.y = y - knob.height / 2;
            }
        }

        Rectangle {
            anchors.centerIn: parent
            width: parent.width - 12
            height: parent.height - 12
            radius: width / 2
            color: "#D7DBDD" //"#FFFFFF"

            Text{
                anchors.centerIn: parent

                text: name
                color: "black"
                font.bold: true
            }
        }
    }
}

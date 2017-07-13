import QtQuick 2.4

Rectangle {
    id: rectangle1


    width: 30
    height: 30

    Rectangle {
        id: circle
        width: parent.width * 0.8
        height: parent.height * 0.8
        color: "#66ccff"
        radius: width / 2
        antialiasing: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        MouseArea {
            id: mouseArea1
            hoverEnabled: true
            anchors.fill: parent
        }

    }

    StateGroup {

        states: [
            State {
                when:mouseArea1.containsMouse

                PropertyChanges {
                    target: circle
                    width: parent.width
                    height: parent.height
                }

            },

            State {
                when: mouseArea1.pressed

                PropertyChanges {
                    target: circle
                    border.color: "#f9b43b"
                }

            }

        ]

    }



}


import QtQuick 2.12
import QtQuick.Window 2.12

Window
{
    visible: true
    width: 800
    height: 480
    //title: qsTr("Hello World")
    color: "black"

    property int counter: 0

    FontLoader
    {
        id: fontHelvetica
        source:"qrc:/images/helvetica.ttf"
    }
    Rectangle
    {
        id: rectInputs
        width: 570
        height: 180
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 10
        color: "transparent"
        border.color: "white"
        border.width: 2
        radius: 10


        Text
        {
            text: qsTr("INPUTS")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            color: "white"
            font.family: fontHelvetica.name
            font.pointSize: 20
        }

        /////////////////////////////////////////////////////////
        // IN1
        /////////////////////////////////////////////////////////
        Rectangle
        {
            id: rectCnt1
            width: 80
            height: width
            radius: width / 2
            anchors.left: parent.left
            anchors.leftMargin: 50
            anchors.top: parent.top
            anchors.topMargin: 60
            color: "transparent"
            border.width: 2
            border.color: "green"

            Rectangle
            {
                id: inctrl1
                width: 60
                height: width
                radius: width / 2
                anchors.centerIn: parent
                color: "transparent"
            }
        }

        Text
        {
            text: "IN 1"
            anchors.horizontalCenter: rectCnt1.horizontalCenter
            anchors.top: rectCnt1.bottom
            anchors.topMargin: 10
            color: "white"
            font.family: fontHelvetica.name
            font.pointSize: 15
        }

        /////////////////////////////////////////////////////////
        // IN2
        /////////////////////////////////////////////////////////
        Rectangle
        {
            id: rectCnt2
            width: 80
            height: width
            radius: width / 2
            anchors.left: rectCnt1.right
            anchors.leftMargin: 50
            anchors.top: parent.top
            anchors.topMargin: 60
            color: "transparent"
            border.width: 2
            border.color: "green"

            Rectangle
            {
                id: inctrl2
                width: 60
                height: width
                radius: width / 2
                anchors.centerIn: parent
                color: "transparent"
            }
        }

        Text
        {
          text: "IN 2"
          anchors.horizontalCenter: rectCnt2.horizontalCenter
          anchors.top: rectCnt1.bottom
          anchors.topMargin: 10
          color: "white"
          font.family: fontHelvetica.name
          font.pointSize: 15
        }

        /////////////////////////////////////////////////////////
        // IN3
        /////////////////////////////////////////////////////////
        Rectangle
        {
            id: rectCnt3
            width: 80
            height: width
            radius: width / 2
            anchors.left: rectCnt2.right
            anchors.leftMargin: 50
            anchors.top: parent.top
            anchors.topMargin: 60
            color: "transparent"
            border.width: 2
            border.color: "green"

            Rectangle
            {
                id: inctrl3
                width: 60
                height: width
                radius: width / 2
                anchors.centerIn: parent
                color: "transparent"
            }
        }

        Text
        {
          text: "IN 3"
          anchors.horizontalCenter: rectCnt3.horizontalCenter
          anchors.top: rectCnt1.bottom
          anchors.topMargin: 10
          color: "white"
          font.family: fontHelvetica.name
          font.pointSize: 15
        }

        /////////////////////////////////////////////////////////
        // IN4
        /////////////////////////////////////////////////////////
        Rectangle
        {
            id: rectCnt4
            width: 80
            height: width
            radius: width / 2
            anchors.left: rectCnt3.right
            anchors.leftMargin: 50
            anchors.top: parent.top
            anchors.topMargin: 60
            color: "transparent"
            border.width: 2
            border.color: "green"

            Rectangle
            {
                id: inctrl4
                width: 60
                height: width
                radius: width / 2
                anchors.centerIn: parent
                color: "transparent"
            }
        }

        Text
        {
          text: "IN 4"
          anchors.horizontalCenter: rectCnt4.horizontalCenter
          anchors.top: rectCnt1.bottom
          anchors.topMargin: 10
          color: "white"
          font.family: fontHelvetica.name
          font.pointSize: 15
        }
    }

    /////////////////////////////////////////////////////////
    // Relay 1
    /////////////////////////////////////////////////////////
    Rectangle
    {
        id: rectRelay1
        width: 128
        height: 128
        anchors.top: rectInputs.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 4
        color: "transparent"
        border.color: "white"
        border.width: 1
        radius: 10

        Text
        {
            text: "Relay 1"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            font.pixelSize: 20
            font.family: fontHelvetica.name
            color: "white"
        }

        Switch
        {
            id: swRelay1
            anchors.top: parent.top
            anchors.topMargin: 60
            anchors.horizontalCenter: parent.horizontalCenter
            backgroundWidth: 100
            backgroundHeight: 50
            //colore: "#FFA500"//"#67bf31"

            onSwitched:
            {
                if(on === true)
                {
                    appBridge.setRelay(1, "ON");
                } else
                {
                    appBridge.setRelay(1, "OFF");
                }
            }
        }
    }

    /////////////////////////////////////////////////////////
    // Relay 2
    /////////////////////////////////////////////////////////
    Rectangle
    {
        id: rectRelay2
        width: 128
        height: 128
        anchors.top: rectInputs.bottom
        anchors.topMargin: 10
        anchors.left: rectRelay1.right
        anchors.leftMargin: 5
        color: "transparent"
        border.color: "white"
        border.width: 1
        radius: 10

        Text
        {
            text: "Relay 2"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            font.pixelSize: 20
            font.family: fontHelvetica.name
            color: "white"
        }

        Switch
        {
            id: swRelay2
            anchors.top: parent.top
            anchors.topMargin: 60
            anchors.horizontalCenter: parent.horizontalCenter
            backgroundWidth: 100
            backgroundHeight: 50

            onSwitched:
            {
                if(on === true)
                {
                    appBridge.setRelay(2, "ON");
                } else
                {
                    appBridge.setRelay(2, "OFF");
                }
            }
        }
    }

    /////////////////////////////////////////////////////////
    // Relay 3
    /////////////////////////////////////////////////////////
    Rectangle
    {
        id: rectRelay3
        width: 128
        height: 128
        anchors.top: rectInputs.bottom
        anchors.topMargin: 10
        anchors.left: rectRelay2.right
        anchors.leftMargin: 5
        color: "transparent"
        border.color: "white"
        border.width: 1
        radius: 10

        Text
        {
            text: "Relay 3"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            font.pixelSize: 20
            font.family: fontHelvetica.name
            color: "white"
        }

        Switch
        {
            id: swRelay3
            anchors.top: parent.top
            anchors.topMargin: 60
            anchors.horizontalCenter: parent.horizontalCenter
            backgroundWidth: 100
            backgroundHeight: 50

            onSwitched:
            {
                if(on === true)
                {
                    appBridge.setRelay(3, "ON");
                } else
                {
                    appBridge.setRelay(3, "OFF");
                }
            }
        }
    }

    /////////////////////////////////////////////////////////
    // Relay 4
    /////////////////////////////////////////////////////////
    Rectangle
    {
        id: rectRelay4
        width: 128
        height: 128
        anchors.top: rectInputs.bottom
        anchors.topMargin: 10
        anchors.left: rectRelay3.right
        anchors.leftMargin: 5
        color: "transparent"
        border.color: "white"
        border.width: 1
        radius: 10

        Text
        {
            text: "Relay 4"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            font.pixelSize: 20
            font.family: fontHelvetica.name
            color: "white"
        }

        Switch
        {
            id: swRelay4
            anchors.top: parent.top
            anchors.topMargin: 60
            anchors.horizontalCenter: parent.horizontalCenter
            backgroundWidth: 100
            backgroundHeight: 50

            onSwitched:
            {
                if(on === true)
                {
                    appBridge.setRelay(4, "ON");
                } else
                {
                    appBridge.setRelay(4, "OFF");
                }
            }
        }
    }

    /////////////////////////////////////////////////////////
    // Relay 5
    /////////////////////////////////////////////////////////
    Rectangle
    {
        id: rectRelay5
        width: 128
        height: 128
        anchors.top: rectInputs.bottom
        anchors.topMargin: 10
        anchors.left: rectRelay4.right
        anchors.leftMargin: 5
        color: "transparent"
        border.color: "white"
        border.width: 1
        radius: 10

        Text
        {
            text: "Relay 5"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            font.pixelSize: 20
            font.family: fontHelvetica.name
            color: "white"
        }

        Switch
        {
            id: swRelay5
            anchors.top: parent.top
            anchors.topMargin: 60
            anchors.horizontalCenter: parent.horizontalCenter
            backgroundWidth: 100
            backgroundHeight: 50

            onSwitched:
            {
                if(on === true)
                {
                    appBridge.setRelay(5, "ON");
                } else
                {
                    appBridge.setRelay(5, "OFF");
                }
            }
        }
    }

    /////////////////////////////////////////////////////////
    // Relay 6
    /////////////////////////////////////////////////////////
    Rectangle
    {
        id: rectRelay6
        width: 128
        height: 128
        anchors.top: rectInputs.bottom
        anchors.topMargin: 10
        anchors.left: rectRelay5.right
        anchors.leftMargin: 5
        color: "transparent"
        border.color: "white"
        border.width: 1
        radius: 10

        Text
        {
            text: "Relay 6"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            font.pixelSize: 20
            font.family: fontHelvetica.name
            color: "white"
        }

        Switch
        {
            id: swRelay6
            anchors.top: parent.top
            anchors.topMargin: 60
            anchors.horizontalCenter: parent.horizontalCenter
            backgroundWidth: 100
            backgroundHeight: 50

            onSwitched:
            {
                if(on === true)
                {
                    appBridge.setRelay(6, "ON");
                } else
                {
                    appBridge.setRelay(6, "OFF");
                }
            }
        }
    }

    /////////////////////////////////////////////////////////
    // Relay 7
    /////////////////////////////////////////////////////////
    Rectangle
    {
        id: rectRelay7
        width: 128
        height: 128
        anchors.top: rectRelay1.bottom
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 4
        color: "transparent"
        border.color: "white"
        border.width: 1
        radius: 10

        Text
        {
            text: "Relay 7"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            font.pixelSize: 20
            font.family: fontHelvetica.name
            color: "white"
        }

        Switch
        {
            id: swRelay7
            anchors.top: parent.top
            anchors.topMargin: 60
            anchors.horizontalCenter: parent.horizontalCenter
            backgroundWidth: 100
            backgroundHeight: 50
            //colore: "#FFA500"//"#67bf31"

            onSwitched:
            {
                if(on === true)
                {
                    appBridge.setRelay(7, "ON");
                } else
                {
                    appBridge.setRelay(7, "OFF");
                }
            }
        }
    }

    /////////////////////////////////////////////////////////
    // Relay 8
    /////////////////////////////////////////////////////////
    Rectangle
    {
        id: rectRelay8
        width: 128
        height: 128
        anchors.top: rectRelay1.bottom
        anchors.topMargin: 5
        anchors.left: rectRelay7.right
        anchors.leftMargin: 5
        color: "transparent"
        border.color: "white"
        border.width: 1
        radius: 10

        Text
        {
            text: "Relay 8"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            font.pixelSize: 20
            font.family: fontHelvetica.name
            color: "white"
        }

        Switch
        {
            id: swRelay8
            anchors.top: parent.top
            anchors.topMargin: 60
            anchors.horizontalCenter: parent.horizontalCenter
            backgroundWidth: 100
            backgroundHeight: 50
            //colore: "#FFA500"//"#67bf31"

            onSwitched:
            {
                if(on === true)
                {
                    appBridge.setRelay(8, "ON");
                } else
                {
                    appBridge.setRelay(8, "OFF");
                }
            }
        }
    }

    /////////////////////////////////////////////////////////
    // Relay 9
    /////////////////////////////////////////////////////////
    Rectangle
    {
        id: rectRelay9
        width: 128
        height: 128
        anchors.top: rectRelay1.bottom
        anchors.topMargin: 5
        anchors.left: rectRelay8.right
        anchors.leftMargin: 5
        color: "transparent"
        border.color: "white"
        border.width: 1
        radius: 10

        Text
        {
            text: "Relay 9"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            font.pixelSize: 20
            font.family: fontHelvetica.name
            color: "white"
        }

        Switch
        {
            id: swRelay9
            anchors.top: parent.top
            anchors.topMargin: 60
            anchors.horizontalCenter: parent.horizontalCenter
            backgroundWidth: 100
            backgroundHeight: 50
            //colore: "#FFA500"//"#67bf31"

            onSwitched:
            {
                if(on === true)
                {
                    appBridge.setRelay(9, "ON");
                } else
                {
                    appBridge.setRelay(9, "OFF");
                }
            }
        }
    }

    /////////////////////////////////////////////////////////
    // Relay 10
    /////////////////////////////////////////////////////////
    Rectangle
    {
        id: rectRelay10
        width: 128
        height: 128
        anchors.top: rectRelay1.bottom
        anchors.topMargin: 5
        anchors.left: rectRelay9.right
        anchors.leftMargin: 5
        color: "transparent"
        border.color: "white"
        border.width: 1
        radius: 10

        Text
        {
            text: "Relay 10"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            font.pixelSize: 20
            font.family: fontHelvetica.name
            color: "white"
        }

        Switch
        {
            id: swRelay10
            anchors.top: parent.top
            anchors.topMargin: 60
            anchors.horizontalCenter: parent.horizontalCenter
            backgroundWidth: 100
            backgroundHeight: 50
            //colore: "#FFA500"//"#67bf31"

            onSwitched:
            {
                if(on === true)
                {
                    appBridge.setRelay(10, "ON");
                } else
                {
                    appBridge.setRelay(10, "OFF");
                }
            }
        }
    }

    /////////////////////////////////////////////////////////
    // Relay 11
    /////////////////////////////////////////////////////////
    Rectangle
    {
        id: rectRelay11
        width: 128
        height: 128
        anchors.top: rectRelay1.bottom
        anchors.topMargin: 5
        anchors.left: rectRelay10.right
        anchors.leftMargin: 5
        color: "transparent"
        border.color: "white"
        border.width: 1
        radius: 10

        Text
        {
            text: "Relay 11"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            font.pixelSize: 20
            font.family: fontHelvetica.name
            color: "white"
        }

        Switch
        {
            id: swRelay11
            anchors.top: parent.top
            anchors.topMargin: 60
            anchors.horizontalCenter: parent.horizontalCenter
            backgroundWidth: 100
            backgroundHeight: 50
            //colore: "#FFA500"//"#67bf31"

            onSwitched:
            {
                if(on === true)
                {
                    appBridge.setRelay(11, "ON");
                } else
                {
                    appBridge.setRelay(11, "OFF");
                }
            }
        }
    }

    /////////////////////////////////////////////////////////
    // Relay 12
    /////////////////////////////////////////////////////////
    Rectangle
    {
        id: rectRelay12
        width: 128
        height: 128
        anchors.top: rectRelay1.bottom
        anchors.topMargin: 5
        anchors.left: rectRelay11.right
        anchors.leftMargin: 5
        color: "transparent"
        border.color: "white"
        border.width: 1
        radius: 10

        Text
        {
            text: "Relay 12"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            font.pixelSize: 20
            font.family: fontHelvetica.name
            color: "white"
        }

        Switch
        {
            id: swRelay12
            anchors.top: parent.top
            anchors.topMargin: 60
            anchors.horizontalCenter: parent.horizontalCenter
            backgroundWidth: 100
            backgroundHeight: 50
            //colore: "#FFA500"//"#67bf31"

            onSwitched:
            {
                if(on === true)
                {
                    appBridge.setRelay(12, "ON");
                } else
                {
                    appBridge.setRelay(12, "OFF");
                }
            }
        }
    }

    Connections
    {
        target: appBridge

        onChangedDin1:
        {
            if(value == "on")
                inctrl1.color = "lightgray"
            else
                inctrl1.color = "transparent"
        }

        onChangedDin2:
        {
            if(value == "on")
                inctrl2.color = "lightgray"
            else
                inctrl2.color = "transparent"
        }

        onChangedDin3:
        {
            if(value == "on")
                inctrl3.color = "lightgray"
            else
                inctrl3.color = "transparent"
        }

        onChangedDin4:
        {
            if(value == "on")
                inctrl4.color = "lightgray"
            else
                inctrl4.color = "transparent"
        }

        onChangedRelay1:
        {
            swRelay1.setStatus(value)
        }

        onChangedRelay2:
        {
            swRelay2.setStatus(value)
        }

        onChangedRelay3:
        {
            swRelay3.setStatus(value)
        }

        onChangedRelay4:
        {
            swRelay4.setStatus(value)
        }

        onChangedRelay5:
        {
            swRelay5.setStatus(value)
        }

        onChangedRelay6:
        {
            swRelay6.setStatus(value)
        }

        onChangedRelay7:
        {
            swRelay7.setStatus(value)
        }

        onChangedRelay8:
        {
            swRelay8.setStatus(value)
        }

        onChangedRelay9:
        {
            swRelay9.setStatus(value)
        }

        onChangedRelay10:
        {
            swRelay10.setStatus(value)
        }

        onChangedRelay11:
        {
            swRelay11.setStatus(value)
        }

        onChangedRelay12:
        {
            swRelay12.setStatus(value)
        }
    }
}

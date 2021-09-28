import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import TalDisplay 1.0

Slider {
    property int barHeight: Destiny.dp(6)
    property int handleHeight: Destiny.dp(24)
    property int handleWidth: Destiny.dp(6)

    property real progress: 0.0
    property real secondProgress: 0.0
    property bool enableHover: false

    readonly property real secondPosition: width * secondProgress / maximumValue

    signal hoverAt(var percent)
    signal leave()

    id: rootSlider
    wheelEnabled: false
    onProgressChanged: {
        if (!pressed) {
            value = progress
        }
    }

    style: SliderStyle {
        groove: Item {
             implicitHeight: barHeight
             implicitWidth: control.width
             Rectangle {
                 width: parent.implicitWidth
                 height: parent.implicitHeight
                 radius: barHeight / 2
                 color: "#45494C"
             }
             Rectangle {
                 height: parent.implicitHeight
                 width: secondPosition
                 radius: barHeight / 2
                 color: "#5D6061"
             }
             Rectangle {
                 height: parent.implicitHeight
                 width: styleData.handlePosition
                 radius: barHeight / 2
                 color: "#5E5FBE"
             }
         }
         handle: Rectangle {
             implicitWidth: handleWidth
             implicitHeight: handleHeight
             radius: handleWidth / 2
             color: control.pressed ? "#EAEAEA" : (control.hovered ? "#F0F0F0" : "#FBFCFE")
         }
    }

    MouseArea {
        id: sliderMouseArea
        anchors.fill: parent
        hoverEnabled: true
        propagateComposedEvents: true
        enabled: enableHover

        onClicked: {
            mouse.accepted = false
        }
        onPressed: {
            mouse.accepted = false
        }
        onReleased: {
            mouse.accepted = false
        }

        onMouseXChanged: {
            hoverAt(mouseX / width)
        }
        onEntered: {
            hoverAt(mouseX / width)
        }
        onExited: {
            leave()
        }
    }
}

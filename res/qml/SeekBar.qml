import QtQuick 2.0

import TalDisplay 1.0

Item {

    property int barHeight: Destiny.dp(6)
    property int handleHeight: Destiny.dp(24)
    property int handleWidth: Destiny.dp(6)

    property string barColor: "#45494C"
    property string progressColor: "#5E5FBE"
    property string secondProgressColor: "#5D6061"

    property string handleColor: "#FBFCFE"
    property string handleHoverColor: "#F0F0F0"
    property string handlePressColor: "#EAEAEA"

    property real maxValue: 1.0
    property real minValue: 0.0
    property real value: 0
    property real secondValue: 0.8

    property bool isResponseWhenSeek: false // 拖动时实时反馈

    property bool isHandlePressed: false

    signal valueChangeByUser(var progress)
    signal enter(var progress)
    signal leave(var progress)
    signal hoverAt(var progress)

    readonly property real progressSize: progressWidth(value)

    onProgressSizeChanged: {
        if (!isHandlePressed) {
            handleRect.x = Math.max(progressSize - handleRect.radius, 0)
        }
    }

    id: control

    width: implicitWidth
    height: handleHeight

    MouseArea {
        id: rootMouseArea
        anchors.fill: parent
        hoverEnabled: true

        property int pressedX: 0

        onPressed: {
            pressedX = mouseX
        }

        onReleased: {
            if (Math.abs(mouseX - pressedX) < 10) {
                updateProgress(mouseX)
            }
        }

        onMouseXChanged: {
            hoverAt(calProgress(mouseX))
        }

        onEntered: {
            var v = calProgress(mouseX)
            enter(v)
            hoverAt(v)
        }

        onExited: {
            leave(calProgress(mouseX))
        }
    }

    Rectangle {
        id: backgroundRect
        width: parent.width
        height: barHeight
        anchors.verticalCenter: parent.verticalCenter
        radius: barHeight / 2
        color: barColor
    }

    Rectangle {
        id: secondValueRect
        width: progressWidth(secondValue)
        height: barHeight
        anchors.verticalCenter: parent.verticalCenter
        radius: barHeight / 2
        color: secondProgressColor
    }

    Rectangle {
        id: progressRect
        width: progressSize
        height: barHeight
        anchors.verticalCenter: parent.verticalCenter
        radius: barHeight / 2
        color: progressColor
    }

    Rectangle {
        id: handleRect
        width: handleWidth
        height: handleHeight
        anchors.verticalCenter: parent.verticalCenter
        radius: width / 2
        color: handleMouseArea.state === handleMouseArea.statePressed ? handlePressColor :
               (handleMouseArea.state === handleMouseArea.stateHovered ? handleHoverColor : handleColor)

        MouseArea {
            id: handleMouseArea
            anchors.fill: parent
            drag.target: parent
            drag.axis: Drag.XAxis
            drag.minimumX: 0
            drag.maximumX: control.width - parent.width
            drag.smoothed: false

            onPositionChanged: {
                if (drag.active && isResponseWhenSeek) {
                    updateProgress(parent.x + parent.width / 2)
                }
            }

            onPressed: {
                isHandlePressed = true
            }

            Timer {
                id: progressTimer
                interval: 500
                repeat: false
                onTriggered: {
                    isHandlePressed = false
                }
            }

            onReleased: {
                updateProgress(parent.x + parent.width / 2)
                progressTimer.start()
            }

            onCanceled: {
                isHandlePressed = false
            }
        }
    }

    function updateProgress(offsetX) {
        value = calProgress(offsetX)
        valueChangeByUser(value)
    }

    function calProgress(offsetX) {
        if (width <= 0) return 0
        return (maxValue - minValue) * (offsetX / width) + minValue
    }

    function progressWidth(p) {
        if (p <= minValue) return 0
        else if (p >= maxValue) return width
        return width * (p - minValue) / (maxValue - minValue)
    }
}

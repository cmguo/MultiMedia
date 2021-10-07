import QtQuick 2.0
import ShowBoard 1.0

Item {
    property var volume: quickWidgetParent.volume

    id: volumeBar
    objectName: "volumeBar"
    width: Destiny.dp(56)
    height: Destiny.dp(198)
    rotation: quickWidgetParent.upDown ? 180 : 0

    Rectangle {
        id: contentRect
        width: parent.width
        height: Destiny.dp(186)

        border.width: Destiny.dp(1)
        border.color: "#424C57"
        color: "#2B3034"
        radius: Destiny.dp(4)

        Text {
            width: parent.width
            height: Destiny.dp(40)
            font {
                family: "Microsoft YaHei"
                pixelSize: Destiny.dp(14)
            }
            color: "#FFFFFF"
            opacity: 0.8
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: "音量"
            rotation: quickWidgetParent.upDown ? -180 : 0
        }

        Rectangle {
            id: divider
            width: parent.width
            height: Destiny.dp(1)
            anchors.top: parent.top
            anchors.topMargin: Destiny.dp(40)
            color: "#424C59"
        }

        Item {
            anchors.top: divider.bottom
            anchors.topMargin: Destiny.dp(8)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Destiny.dp(8)
            width: parent.width
            height: implicitHeight
            rotation: quickWidgetParent.upDown ? -180 : 0

            BarSlider {
                id: volumeSlider
                objectName: "volumeSlider"
                width: parent.height
                height: Destiny.dp(24)
                anchors.centerIn: parent
                wheelEnabled: true

                rotation: -90
                value: volume

                onValueChanged: {
                    quickWidgetParent.volume = value
                }
            }
        }
    }

    Image {
        id: arrowDownImg
        width: Destiny.dp(32)
        height: Destiny.dp(12)
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Destiny.dp(1)
        source: "qrc:/multimedia/image/ic_audio_arrow_down.png"
    }
}

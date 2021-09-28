import QtQuick 2.0
import QtGraphicalEffects 1.12
import QtAV 1.7
import ShowBoard 1.0

Rectangle {
    property bool isPlaying: false
    property bool showLoading: false
    property real bufferProgress: 0.0

    property string mediaTitle: quickWidgetParent.mediaTitle
    property var mediaUrl: quickWidgetParent.mediaUrl

    property var totalTime: 1  // 播放总时长
    property var currentTime: 0 // 当前时间

    property bool isFold: false //是否是折叠状态
    property int animationDuration: 300
    property int loadingAnimationDuration: 1000

    id: audioPlayer
    width: quickWidgetParent.canResize ? audioPlayerBar.width : Destiny.dp(472)
    height: audioPlayerBar.height
    color: "#01FF0000"

    onCurrentTimeChanged: {
        seekSlider.value = currentTime
    }

    Timer {
        id: playTimer
        interval: 200
        repeat: false
        onTriggered: function() {
            console.log("audio player start play")
            player.play()
        }
    }

    onMediaUrlChanged: {
        console.log("audio player media url changed: ", isPlaying, mediaUrl)
        if (isPlaying) {
            player.stop()
        }
        player.source = mediaUrl

        if (mediaUrl !== "") {
            playTimer.start()
        }
    }

    Rectangle {
        id: audioPlayerBar
        objectName: "audioPlayerBar"
        width: playerBtnRect.width + folderBtnItem.width + folderBtnItem.anchors.rightMargin + folderArea.width
        height: Destiny.dp(72)
        anchors.bottom: parent.bottom

        border.width: Destiny.dp(1)
        border.color: "#424C57"
        color: "#2B3034"
        radius: height / 2

        // 播放按钮
        Item {
            id: playerBtnRect
            width: parent.height
            height: parent.height
            anchors.left: parent.left
            anchors.leftMargin: Destiny.dp(1)
            clip: true

            Image {
                id: playerBgImg
                anchors.fill: parent
                source: "qrc:/resource/image/audio_play_btn_bg.png"
            }

            Image {
                id: playerBtnImg
                width: Destiny.dp(40)
                height: Destiny.dp(40)
                anchors.centerIn: parent
                visible: !showLoading
                opacity: playerBtnMouseArea.state === playerBtnMouseArea.stateHovered ? 0.8 : (playerBtnMouseArea.state === playerBtnMouseArea.statePressed ? 0.5 : 1)
                source: isPlaying ? "qrc:/resource/image/ic_media_pause.png" : "qrc:/resource/image/ic_media_play.png"
            }

            Image {
                id: loadingImg
                width: Destiny.dp(40)
                height: Destiny.dp(40)
                anchors.centerIn: parent
                opacity: playerBtnMouseArea.state === playerBtnMouseArea.stateHovered ? 0.8 : (playerBtnMouseArea.state === playerBtnMouseArea.statePressed ? 0.5 : 1)
                source: "qrc:/resource/image/ic_media_loading.png"
                visible: showLoading
            }

            PropertyAnimation {
                id: loadingAnimation
                from: 0
                to: 360
                loops: Animation.Infinite
                target: loadingImg
                duration: loadingAnimationDuration
                property: "rotation"
                running: loadingImg.visible
            }

            RoundProgress {
                id: roundProgress
                anchors.fill: parent
                anchors.margins: Destiny.dp(2)
                progress: currentTime * 1.0 / totalTime
                opacity: isFold ? 1 : 0
                Behavior on opacity {
                    PropertyAnimation { duration: animationDuration; easing.type: Easing.InOutCubic; }
                }
            }

            MouseArea {
                id: playerBtnMouseArea
                anchors.fill: parent

                onClicked: {
                    quickWidgetParent.showVolumeBar = false
                    if (isPlaying) {
                        player.pause()
                    } else {
                        player.play()
                    }
                }
            }
        }

        // 中间能折叠的区域
        Item {
            id: folderArea
            height: parent.height
            width: isFold ? 0 : Destiny.dp(362)
            opacity: isFold ? 0 : 1
            anchors.left: playerBtnRect.right
            Behavior on width {
                PropertyAnimation { duration: animationDuration; easing.type: Easing.InOutCubic; }
            }
            Behavior on opacity {
                PropertyAnimation { duration: animationDuration; easing.type: Easing.InOutCubic; }
            }

            // 播放时间，进度，标题
            Item {
                id: infoContainer
                width: Destiny.dp(240)
                height: parent.height
                anchors.left: parent.left
                anchors.leftMargin: Destiny.dp(16)

                Item {
                    id: titleArea
                    width: parent.width
                    height: Destiny.dp(19)
                    anchors.top: parent.top
                    anchors.topMargin: Destiny.dp(12)
                    clip: true

                    Text {
                        id: titleText
                        height: parent.height
                        width: implicitWidth
                        font {
                            family: "Microsoft YaHei"
                            pixelSize: Destiny.dp(14)
                        }
                        color: "#FFFFFF"
                        opacity: 0.8
                        text: mediaTitle

                        onTextChanged: {
                            titleText.x = 0
                            marqueeAnimation.stop()

                            var showMarquee = titleText.width > titleArea.width
                            leftGradient.visible = showMarquee
                            rightGradient.visible = showMarquee

                            if (showMarquee) {
                                marqueeAnimation.to = -1 * titleText.width
                                marqueeAnimation.duration = titleText.width * 20
                                marqueeAnimation.start()
                            }
                        }

                        PropertyAnimation {
                            id: marqueeAnimation
                            running: false
                            property: "x"
                            target: titleText
                            from: 0
                            to: 0
                            duration: 8000
                            loops: Animation.Infinite
                        }
                    }

                    LinearGradient {
                        id: leftGradient
                        height: parent.height
                        width: Destiny.dp(40)
                        visible: false
                        start: Qt.point(0, 0)
                        end: Qt.point(width, 0)
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: "#FF2B3034" }
                            GradientStop { position: 1.0; color: "#002B3034" }
                        }
                    }

                    LinearGradient {
                        id: rightGradient
                        height: parent.height
                        width: Destiny.dp(40)
                        visible: false
                        anchors.right: parent.right
                        start: Qt.point(0, 0)
                        end: Qt.point(width, 0)
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: "#002B3034" }
                            GradientStop { position: 1.0; color: "#FF2B3034" }
                        }
                    }
                }

                Item {
                    id: timeBar
                    width: parent.width
                    height: Destiny.dp(24)
                    anchors.top: titleArea.bottom
                    anchors.topMargin: Destiny.dp(5)

                    Text {
                        id: currentTimeText
                        width: implicitWidth
                        height: parent.height
                        verticalAlignment: Text.AlignVCenter
                        font {
                            family: "Microsoft YaHei"
                            pixelSize: Destiny.dp(12)
                        }
                        color: "#FFFFFF"

                        text: formatTime(currentTime)
                    }

                    Text {
                        id: totalTimeText
                        width: implicitWidth
                        height: parent.height
                        verticalAlignment: Text.AlignVCenter
                        anchors.right: parent.right
                        font {
                            family: "Microsoft YaHei"
                            pixelSize: Destiny.dp(12)
                        }
                        color: "#FFFFFF"

                        text: formatTime(totalTime)
                    }

                    SeekBar {
                        id: seekSlider
                        objectName: "seekSlider"
                        width: parent.width - currentTimeText.width - totalTimeText.width - anchors.leftMargin - anchors.rightMargin
                        height: parent.height

                        anchors.left: currentTimeText.right
                        anchors.leftMargin: Destiny.dp(8)
                        anchors.right: totalTimeText.left
                        anchors.rightMargin: Destiny.dp(8)

                        maxValue: totalTime
                        value: currentTime
                        secondValue: bufferProgress * totalTime
                        onValueChangeByUser: {
                            player.seek(progress)
                        }
                    }
                }
            }

            // 音量按钮
            Item {
                id: volumeBtnItem
                objectName: "volumeButton"
                width: Destiny.dp(48)
                height: Destiny.dp(48)
                anchors.left: infoContainer.right
                anchors.leftMargin: Destiny.dp(8)
                anchors.verticalCenter: parent.verticalCenter

                Image {
                    id: volumeBtnImg
                    width: Destiny.dp(32)
                    height: Destiny.dp(32)
                    anchors.centerIn: parent
                    opacity: volumeBtnMouseArea.state === volumeBtnMouseArea.stateHovered ? 0.8 : (volumeBtnMouseArea.state === volumeBtnMouseArea.statePressed ? 0.5 : 1)
                    source: volumeBar.volume < 0.01 ? "qrc:/resource/image/ic_audio_off.svg" : "qrc:/resource/image/ic_audio_on.svg"
                }

                MouseArea {
                    id: volumeBtnMouseArea
                    anchors.fill: parent

                    onClicked: {
                        quickWidgetParent.volumeClick()
                    }

                    onDoubleClicked: {
                        quickWidgetParent.volumeClick()
                    }
                }
            }

            // 关闭按钮
            Item {
                id: closeBtnItem
                width: Destiny.dp(48)
                height: Destiny.dp(48)
                anchors.left: volumeBtnItem.right
                anchors.verticalCenter: parent.verticalCenter

                Image {
                    id: closeBtnImg
                    width: Destiny.dp(32)
                    height: Destiny.dp(32)
                    anchors.centerIn: parent
                    opacity: closeBtnMouseArea.state === closeBtnMouseArea.stateHovered ? 0.8 : (closeBtnMouseArea.state === closeBtnMouseArea.statePressed ? 0.5 : 1)
                    source: "qrc:/resource/image/ic_audio_close.svg"
                }

                MouseArea {
                    id: closeBtnMouseArea
                    anchors.fill: parent
                    onClicked: {
                        quickWidgetParent.showVolumeBar = false
                        quickWidgetParent.closeClick()
                        stop()
                    }
                }
            }

            Rectangle {
                id: splitRect
                width: Destiny.dp(2)
                height: Destiny.dp(36)
                anchors.left: closeBtnItem.right
                anchors.verticalCenter: parent.verticalCenter
                color: "#434D59"
            }
        }

        // 折叠按钮
        Item {
            id: folderBtnItem
            width: Destiny.dp(32)
            height: Destiny.dp(32)
            anchors.left: folderArea.right
            anchors.rightMargin: Destiny.dp(4)
            anchors.verticalCenter: parent.verticalCenter

            Image {
                id: folderImg
                width: Destiny.dp(20)
                height: Destiny.dp(20)
                anchors.centerIn: parent
                opacity: folderBtnMouseArea.state === folderBtnMouseArea.stateHovered ? 0.8 : (folderBtnMouseArea.state === folderBtnMouseArea.statePressed ? 0.5 : 1)
                source: "qrc:/resource/image/ic_audio_fold.svg"
                rotation: isFold ? 180 : 0

                Behavior on rotation {
                    PropertyAnimation { duration: animationDuration; easing.type: Easing.InOutCubic; }
                }
            }

            MouseArea {
                id: folderBtnMouseArea
                anchors.fill: parent
                onClicked: {
                    isFold = !isFold
                    quickWidgetParent.showVolumeBar = false
                }
            }
        }
    }

    MediaPlayer {
        id: player
        objectName: "player"
        autoPlay: false
//        source: mediaUrl
        volume: volumeBar.volume
        onPositionChanged: {
            audioPlayer.currentTime = position
        }
        onSourceChanged: {
            console.log("audio player: playing source: ", source)
        }
        onDurationChanged: {
            if (isPlaying) {
                audioPlayer.totalTime = duration
            }
        }
        onPlaying: {
            isPlaying = true
        }
        onStopped: {
            isPlaying = false
            currentTime = 0
        }
        onPaused: {
            isPlaying = false
        }
        onError: {
            console.error("audio player error: ", error, "; current source: ", mediaUrl)
        }
        onBufferProgressChanged: {
            audioPlayer.bufferProgress = bufferProgress
        }
        onStatusChanged: {
            if (status === MediaPlayer.Loading) {
            } else if (status === MediaPlayer.Buffering) {
                showLoading = true
            } else if (status === MediaPlayer.Buffered) {
                audioPlayer.bufferProgress = 1
                showLoading = false
            } else if (status === MediaPlayer.EndOfMedia) {
            } else if (status === MediaPlayer.InvalidMedia) {
            }
        }
    }

    function stop() {
        player.stop()
        quickWidgetParent.mediaTitle = ""
        quickWidgetParent.mediaUrl = ""
    }

    function formatTime(time) {
        time = parseInt(time / 1000)
        var minute = parseInt(time / 60)
        var second = time % 60
        var result = ""

        if (minute < 10) {
            result += "0"
        }
        result += minute
        result += ":"
        if (second < 10) {
            result += "0"
        }
        result += second

        return result
    }
}

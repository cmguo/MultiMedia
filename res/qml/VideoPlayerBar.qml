import QtQuick 2.12
import QtQuick.Controls 2.12
import TalDisplay 1.0
import MediaPlayer 1.0
import "qrc:/uibase/qml/talwidget"
import "qrc:/uibase/qml/talwidget/styles"

Item {
    property int animationDuration: 300
    property int loadingAnimationDuration: 1000

    property int playPosition: player.position
    onPlayPositionChanged: {
        if(playPosition >= (player.duration-800) && player.playState === MediaPlayer.PlayingState){ // 帧率一般30/s
            player.position = 800;
            player.playState = MediaPlayer.PausedState
        }
        seekSlider.value = playPosition
    }

    id: rootBar

    TalMouseArea {
        width: parent.width
        height: parent.height-controlBar.height
        onClicked: togglePlayAndPaused()
        onDoubleClicked: togglePlayAndPaused()
    }
    TalMouseArea {
        anchors.bottom: parent.bottom
        height: controlBar.height
        width: parent.width
        onClicked: {
            if(player.playState !== MediaPlayer.PlayingState)
                return;
            controlBar.visible = true;
            handler.delay(3000,function() {
                if (volumeBar.opened) return
                if(player.playState === MediaPlayer.PlayingState)
                    controlBar.visible = false;
            })
        }
        hoverEnabled: true
        onEntered:  {
            if(player.playState !== MediaPlayer.PlayingState)
                return;
            controlBar.visible = true;

        }
        onExited: {
            if(player.playState !== MediaPlayer.PlayingState)
                return;
            handler.delay(3000,function() {
                if (volumeBar.opened) return
                if(player.playState === MediaPlayer.PlayingState)
                    controlBar.visible = false;
            })
        }
    }
    TalHandler {
        id: handler
    }

    TalHandler {
        id: resetStartPositionHandler
    }
    Rectangle{
        height: Destiny.dp(128)
        width:Destiny.dp(128)
        radius: height/2
        color: "#80000000"
        anchors.centerIn: parent
        visible: player.playState !== MediaPlayer.PlayingState
        Image {
            id:centeStateBtn
            height: Destiny.dp(88)
            width:Destiny.dp(88)
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
            opacity: centeStateBtnArea.state === centeStateBtnArea.stateHovered
                     ? 0.8 : (centeStateBtnArea.state === centeStateBtnArea.statePressed ? 0.5 : 1)
            source: player.playState === MediaPlayer.LoadingState
                    ? "qrc:/resource/image/ic_media_loading.png":player.playState === MediaPlayer.PlayingState
                      ? "qrc:/resource/image/ic_media_pause.png"
                      : "qrc:/resource/image/ic_media_play.png"

            TalMouseArea {
                id: centeStateBtnArea
                anchors.fill: parent
                onClicked: togglePlayAndPaused()
                onDoubleClicked: togglePlayAndPaused()
            }
        }

        PropertyAnimation {
            from: true
            to: 360
            loops: Animation.Infinite
            target: centeStateBtn
            duration: loadingAnimationDuration
            property: "rotation"
            running: player.playState===MediaPlayer.LoadingState
            onRunningChanged:
                if(!running)
                    centeStateBtn.rotation = 0;
        }
    }

    Rectangle{
        id:controlBar
        color: "#FF2B3034"
        radius: control.fullScreen?Destiny.dp(8):0
        border.color: "#434D59"
        border.width: control.fullScreen?Destiny.dp(1):0
        height:Destiny.dp(48)
        width: control.fullScreen?Destiny.dp(680):parent.width
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: control.fullScreen?Destiny.dp(16):0
        Connections {
            target: player
            onPlayStateChanged:{
                if(player.playState === MediaPlayer.PlayingState)
                    resetStartPositionHandler.delay(1000,function(){
                         player.startPosition = 0;
                    });
                controlBarAutoHide();
            }
        }
        Component.onCompleted: {
            controlBarAutoHide(); //已经在播放的控制，eg播放情况下点击全屏
        }

        onVisibleChanged: {
            if(!visible)
               volumeBar.close();
        }

        Row{
            id: leftRegion
            height: parent.height
            spacing: Destiny.dp(16)
            leftPadding:spacing
            rightPadding:Destiny.dp(8)
            Image {
                id: playerBtnImg
                height: Destiny.dp(32)
                fillMode: Image.PreserveAspectFit
                anchors.verticalCenter: parent.verticalCenter
                opacity: playerBtnMouseArea.state === playerBtnMouseArea.stateHovered
                         ? 0.8 : (playerBtnMouseArea.state === playerBtnMouseArea.statePressed ? 0.5 : 1)
                source: player.playState === MediaPlayer.LoadingState
                        ? "qrc:/resource/image/ic_media_loading.png":player.playState === MediaPlayer.PlayingState
                          ? "qrc:/resource/image/ic_media_pause.png"
                          : "qrc:/resource/image/ic_media_play.png"

                TalMouseArea {
                    id: playerBtnMouseArea
                    anchors.fill: parent
                    onClicked:togglePlayAndPaused();
                }
            }

            PropertyAnimation {
                id: loadingAnimation
                from: 0
                to: 360
                loops: Animation.Infinite
                target: playerBtnImg
                duration: loadingAnimationDuration
                property: "rotation"
                running: player.playState===MediaPlayer.LoadingState
                onRunningChanged:
                    if(!running)
                        playerBtnImg.rotation = 0;
            }

            TalText {
                id: currentTimeText
                width: implicitWidth
                height: parent.height
                verticalAlignment: Text.AlignVCenter

                talStyle: TalTextStyleWhite {
                    size: TalTextStyle.Size.AssistSecondary
                }
                text: formatTime(player.position)
            }

        }

        TalSeekBar {
            id: seekSlider
            objectName: "seekSlider"
            width: parent.width - leftRegion.width -rightRegion.width
            height: parent.height
            anchors.left: leftRegion.right
            maxValue: player.duration
            value:player.position
//            secondValue: player.bufferProgress
            onValueChangeByUser: {
                player.position = progress
            }
        }
        Row{
            id: rightRegion
            height: parent.height
            spacing: Destiny.dp(16)
            layoutDirection:Qt.RightToLeft
            anchors.right: parent.right
            rightPadding:spacing
            leftPadding:Destiny.dp(8)

            Image {
                id: fullScreenBtn
                height: Destiny.dp(32)
                fillMode: Image.PreserveAspectFit
                anchors.verticalCenter: parent.verticalCenter
                opacity: fullScreenBtnMouseArea.state === fullScreenBtnMouseArea.stateHovered ? 0.8 : (fullScreenBtnMouseArea.state === fullScreenBtnMouseArea.statePressed ? 0.5 : 1)
                source: control.fullScreen ? "qrc:/resource/image/exit_fullscreen.png" : "qrc:/resource/image/fullscreen.png"
                TalMouseArea {
                    id: fullScreenBtnMouseArea
                    anchors.fill: parent
                    onClicked: {
                        control.fullScreen = !control.fullScreen;
                    }
                }
            }
            Item {
                id: feedbackBtn
                objectName: "feedbackBtn"
                height: parent.height
                width: Destiny.dp(60)
                visible: quickWidgetParent.enableFeedBack
                opacity: feedbackBtnArea.state === feedbackBtnArea.stateHovered ? 0.8 : (feedbackBtnArea.state === feedbackBtnArea.statePressed ? 0.5 : 1)
                Image {
                    anchors.left: parent.left
                    height: Destiny.dp(32)
                    fillMode: Image.PreserveAspectFit
                    anchors.verticalCenter: parent.verticalCenter
                    source: "qrc:/resource/image/feedback.png"
                }
                TalText {
                    width: implicitWidth
                    height: parent.height
                    anchors.right: parent.right
                    verticalAlignment: Text.AlignVCenter

                    talStyle: TalTextStyleWhite {
                        size: TalTextStyle.Size.AssistSecondary
                    }
                    text:"反馈"
                }
                TalMouseArea {
                    id: feedbackBtnArea
                    anchors.fill: parent
                    onClicked: {
                        var locationToRoot = mapToItem(rootBar, feedbackBtn.width / 2, feedbackBtn.height / 2)
                        quickWidgetParent.feedback(locationToRoot);
                    }
                }

            }

            Image {
                id: volumeBtnImg
                height: Destiny.dp(32)
                fillMode: Image.PreserveAspectFit
                anchors.verticalCenter: parent.verticalCenter
                opacity: volumeBtnMouseArea.state === volumeBtnMouseArea.stateHovered ? 0.8 : (volumeBtnMouseArea.state === volumeBtnMouseArea.statePressed ? 0.5 : 1)
                source: player.volume < 0.01 ? "qrc:/resource/image/ic_audio_off.svg" : "qrc:/resource/image/ic_audio_on.svg"
                TalMouseArea {
                    id: volumeBtnMouseArea
                    anchors.fill: parent
                    onClicked: {
                        volumeBar.open();
                    }
                }
            }

            TalText {
                id: totalTimeText
                width: implicitWidth
                height: parent.height
                verticalAlignment: Text.AlignVCenter

                talStyle: TalTextStyleWhite {
                    size: TalTextStyle.Size.AssistSecondary
                }
                text: formatTime(player.duration)
            }
        }

    }

    Popup {
        x: controlBar.x + rightRegion.x + volumeBtnImg.x - (width - volumeBtnImg.width) / 2
        closePolicy: Popup.CloseOnPressOutside
        id: volumeBar
        width: Destiny.dp(56)
        height: Destiny.dp(198)
        y:controlBar.y - height
        modal:true
        dim: false
        background: Rectangle {
            anchors.fill: parent
            color: "transparent"
        }
        contentItem:Rectangle {
            id: contentRect
            color: "transparent"
            anchors.fill: parent
            Rectangle{
                width: contentRect.width
                height: Destiny.dp(186)
                border.width: Destiny.dp(1)
                border.color: "#424C57"
                color: "#2B3034"
                radius: Destiny.dp(4)
                anchors.top: contentRect.top
                TalText {
                    width: parent.width
                    height: Destiny.dp(40)
                    talStyle: TalTextStyleWhite {
                        size: TalTextStyle.Size.AssistPrimary
                        level: TalTextStyle.ColorLevel.L80
                    }
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: "音量"
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

                    BarSlider {
                        id: volumeSlider
                        objectName: "volumeSlider"
                        width: parent.height
                        height: Destiny.dp(24)
                        anchors.centerIn: parent

                        rotation: -90
                        value: player.volume

                        onValueChanged: {
                            if(player.volume!==value)
                                player.volume = value
                        }
                    }
                }
            }

            Image {
                id: arrowDownImg
                width: Destiny.dp(32)
                fillMode: Image.PreserveAspectFit
                anchors.horizontalCenter: contentRect.horizontalCenter
                anchors.bottom: contentRect.bottom
                anchors.bottomMargin: Destiny.dp(1)
                source: "qrc:/resource/image/ic_audio_arrow_down.png"
            }
        }
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

    function togglePlayAndPaused(){
        if(player.playState === MediaPlayer.PlayingState)
            player.playState = MediaPlayer.PausedState
        else
            player.playState = MediaPlayer.PlayingState
    }

    function controlBarAutoHide(){
        if (volumeBar.opened) return

        if(player.playState === MediaPlayer.PlayingState)
            handler.delay(3000,function() {
                if(player.playState === MediaPlayer.PlayingState)
                    controlBar.visible = false;
            })
        else
            handler.delay(0,function() {
                if(player.playState !== MediaPlayer.LoadingState)
                    controlBar.visible = true;
            });
    }
}

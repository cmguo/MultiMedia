import QtQuick 2.0

Canvas {

    property var maxValue: 1.0
    property var progress: 0.0

    property int strokeWidth: 6
    property int progressWidth: 4

    property string strokeColor: "#202020"
    property string progressColor: "#5E5FBE"

    onPaint: {
        var ctx = getContext("2d")
        if (ctx === null) return

        ctx.clearRect(0, 0, width, height)

        ctx.beginPath()
        ctx.strokeStyle = strokeColor
        ctx.lineWidth = strokeWidth
        ctx.arc(width / 2, height / 2, width / 2 - strokeWidth / 2, 0, Math.PI * 2)
        ctx.stroke()

        var progressAngle = progress / maxValue * 2 * Math.PI

        ctx.save()
        ctx.beginPath()
        ctx.strokeStyle = progressColor
        ctx.lineWidth = progressWidth
        ctx.arc(width / 2, height / 2, width / 2 - strokeWidth / 2,  - Math.PI / 2, progressAngle - Math.PI / 2)
        ctx.stroke()
        ctx.restore()
    }

    onMaxValueChanged: {
        requestPaint()
    }

    onProgressChanged: {
        requestPaint()
    }
}

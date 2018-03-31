import QtQuick 2.9

import "." as Isometry

Isometry.Tile {
    property int sideSize: 0
    property int row: 0
    property int column: 0

    function toRadians(angle) {
        return angle * (Math.PI / 180);
    }

    property real forwardAngleRadians: toRadians(forwardAngle)
    property real sideAngleRadians: toRadians(sideAngle)

    property int cellWidth: sideSize / Math.cos(sideAngleRadians)

    property bool isOddRow: (row % 2) == 1
    property int isometricOffset: isOddRow ? (cellWidth / 2) : 0

    width: sideSize
    height: sideSize

    property bool preventRecursiveXUpdate: true
    function setX() {
        var savedPreventRecursiveXUpdate = preventRecursiveXUpdate
        preventRecursiveXUpdate = !preventRecursiveXUpdate
        if (savedPreventRecursiveXUpdate)
            x = column * cellWidth + isometricOffset
    }

    onXChanged: setX()

    Component.onCompleted: setX()
}

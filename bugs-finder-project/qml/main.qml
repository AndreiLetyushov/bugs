import QtQuick 2.3
import QtQuick.Window 2.1
import OpenGLEngine 1.0

Window {
    Item {
        id: cuttingSceneContainer
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        AnimationRenderer {
            id: animationRenderer
            anchors.left: parent.left
            anchors.leftMargin: 100
            anchors.right: parent.right
            anchors.rightMargin: 100
            anchors.top: parent.top
            anchors.topMargin: 100
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 100
        }
        Component.onCompleted: showMaximized()
    }
}

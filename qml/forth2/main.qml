import QtQuick 2.2
import "contents"
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.1

Rectangle {
     id: page
     width: 1300; height: 690
     Rectangle {
         id: skinpic
         x: 0
         y: 0
         width: parent.width
         height: parent.height

         color: "#000"
//         Text {
//             id: title
//             x: 10
//             y: 10
//             width: 125
//             height: 12
//             color: "#ffffff"
//             text: "泡沫浮选监控系统"
//             font.pointSize: 9
//             font.family: "微软雅黑"
//             font.pixelSize: 12
//         }
         TabWidget
         {
             id: mainwindow
             x: 0;
             y: 10;
             width:parent.width
             height:parent.height
         }

         AnimatedImage{
             id: logo
             anchors.right: parent.right
             anchors.rightMargin: 0
             anchors.top: parent.top
             anchors.topMargin: 0
             width: 200
             height: 85
             source: "contents/xinlonglogo.gif"
         }

//         Image
//         {
//             id: logo
//             anchors.right: parent.right
//             anchors.rightMargin: 20
//             anchors.top: parent.top
//             anchors.topMargin: 10
//             source: "contents/logo.png"
//         }

     }
}


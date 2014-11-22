//锑粗选相机及其特征

import QtQuick 2.0
import QtQuick.Controls 1.1
import SbCamera 1.0
Rectangle
{
    anchors.fill: parent
    anchors.margins: 10
    color:"#00000000"
    Rectangle{
         id:sbcamerarec
         anchors.fill: parent
         anchors.rightMargin: 300
         color:"#707070"
          SbCamera {
            anchors.fill: parent
            id: sbcamera

//                        renderTarget: FramebufferObject
            Timer{
                id: sbcameratimer
                interval: 10
                repeat: true
                onTriggered: {
                    sbtime.text = Date().toString()
//                    sbcamera.getsbimage()
                    sbcamera.updatesbcamera()
                }
            }
            Timer{
                id: sbvaluetimer
                interval: 70000;
                repeat: true
                onTriggered: {
                    imagevalue.getSbImageValue();
                }
            }
            Timer{
                id:sbbuttontimer
                interval: 8000
                running: true///if not connect camera
                repeat: false
                onTriggered: {
                    sbcamera.startsbcamera()
                    sbcameratimer.start()
                    sbvaluetimer.start()
                }
            }

//            Button {
//                id: button2
//                text: "StartsbCamera"
//                iconSource: qsTr("")
//                activeFocusOnPress: false
//                checked: false
//                anchors.left: parent.left
//                anchors.leftMargin: 0
//                anchors.top: parent.top
//                anchors.topMargin: 0
//                onClicked:{
//                    sbcamera.startsbcamera()
//                    sbcameratimer.start()
//                    sbvaluetimer.start()
//                }
//            }
            Text {
                id: sbtime
                text: "time"
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                style: Text.Raised
                font.pointSize: 15
            }
           }
    }
    Rectangle{
        id:sbcharacter
        anchors.top:parent.top
        anchors.left: sbcamerarec.right
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: "gray"
        Rectangle{
            anchors.fill: parent
        Column{
            anchors.top: parent.top
            id:sbpinweiyuce
            width: parent.width
            height: 195
            spacing: 5



        Rectangle{
            width: parent.width
            height: 45
            color: "#000000"
           Text{
                id:pinwei
                anchors.centerIn: parent
                text: "原矿品位预测"
                font.pixelSize:40
                font.italic: true
                color: "#00FFFF"
            }
        }
        Row{
            width: parent.width
            spacing: 6

        Rectangle{
            width: parent.width/2-13
            height: 145
            color: "#000000"
           Text{
                id:pinwei2
                anchors.centerIn: parent
                text: "品位"
                font.pixelSize:50
                font.italic: true
                color: "#00FF00"

            }
        }
        Rectangle{
            width: parent.width/2+7
            height: 145
            color: "#000000"
            ListModel {
                id: sbpinweiModel
                Component.onCompleted: {
                    append({"编号": 1, "名称": "极低 " , "品位范围" :"0~1"})
                    append({"编号": 2, "名称": "A title " , "品位范围" :"0~1"})
                    append({"编号": 3, "名称": "A title " , "品位范围" :"0~1"})
                    append({"编号": 4, "名称": "A title " , "品位范围" :"0~1"})
                    append({"编号": 5, "名称": "A title " , "品位范围" :"0~1"})
                    append({"编号": 6, "名称": "A title " , "品位范围" :"0~1"})
                    append({"编号": 7, "名称": "A title " , "品位范围" :"0~1"})
                    append({"编号": 8, "名称": "A title " , "品位范围" :"0~1"})
                    append({"编号": 9, "名称": "A title " , "品位范围" :"0~1"})
                }
            }
            TableView{
                model: sbpinweiModel
                anchors.fill: parent
                TableViewColumn {
                    role: "编号"
                    title: "#"
                    width: 30
                }
                TableViewColumn {
                    role: "名称"
                    title: "名称"
                    width: 50
                }
                TableViewColumn {
                    role: "品位范围"
                    title: "品位范围"
                    width: 60

                }
            }
        }
        }

}
        Rectangle{

            anchors.top:sbpinweiyuce.bottom
            width: parent.width
            height:18
            color: "#009090"
        }
        Column{
            anchors.top: sbpinweiyuce.bottom
            anchors.topMargin: 15
            anchors.bottom: parent.bottom
            width: parent.width
            spacing: 5

        Rectangle{

            width: parent.width
            height: 45
            color: "#000000"
           Text{
                anchors.centerIn: parent
                text: "泡沫特征"
                font.pixelSize:40
                font.italic: true
                color: "#00FFFF"
            }
        }
        Rectangle{
            id:sbtezheng
            width: parent.width
            height: (parent.height-75)/6
            color: "#000000"
           Text{
                id:sbbubblesize
                anchors.centerIn: parent
                text: "泡沫大小: " +imagevalue.sbBubbleSize
                font.pixelSize:30
                font.italic: true
                color: "#00FF00"
            }
        }
        Rectangle{
            width: parent.width
            height: sbtezheng.height
            color: "#000000"
           Text{
                id:sbbubblenumber
                anchors.centerIn: parent
                text: "泡沫个数: "+imagevalue.sbBubbleNumber
                font.pixelSize:30
                font.italic: true
                color: "#00FF00"
            }
        }
        Rectangle{
            width: parent.width
            height: sbtezheng.height
            color: "#000000"
           Text{
                id:sbgraymean
                anchors.centerIn: parent
                text: "泡沫颜色: "+imagevalue.sbGrayMean
                font.pixelSize:30
                font.italic: true
                color: "#00FF00"
            }
        }
        Rectangle{
            width: parent.width
            height: sbtezheng.height
            color: "#000000"
           Text{
                id:sbbubblefangcha
                anchors.centerIn: parent
                text: "泡沫方差"
                font.pixelSize:30
                font.italic: true
                color: "#00FF00"
            }
        }
        Rectangle{
            width: parent.width
            height: sbtezheng.height
            color: "#000000"
           Text{
                id:sbchengzailv
                anchors.centerIn: parent
                text: "承载率"
                font.pixelSize:30
                font.italic: true
                color: "#00FF00"
            }
        }
        Rectangle{
            width: parent.width
            height: sbtezheng.height
            color: "#000000"
           Text{
                id:sbbubblerate
                anchors.centerIn: parent
                text: "泡沫速度"
                font.pixelSize:30
                font.italic: true
                color: "#00FF00"
            }
        }


        }

}
    }

}

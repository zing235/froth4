//金粗选相机及其特征

import QtQuick 2.0
import QtQuick.Controls 1.1
import AuCamera 1.0
Rectangle
{
    anchors.fill: parent
    anchors.margins: 10
    color:"#00000000"
    Rectangle{
         id:aucamerarec
         anchors.fill: parent
         anchors.rightMargin: 300
         color:"#707070"
          AuCamera {
            anchors.fill: parent
            id: aucamera


            Timer{
                id: aucameratimer
                interval: 1
                repeat: true
                onTriggered: {
                    autime.text = Date().toString()
                    aucamera.getauimage()
                    aucamera.updateaucamera()
                }
            }
            Timer{
                id: auvaluetimer
                interval: 60000;
                repeat: true
                onTriggered: {
                    imagevalue.getAuImageValue();
                    getpinwei();
                }
                function  getpinwei()///???/
                {
                    switch (imagevalue.SbGrade)
                    {
                    case 0 : pinwei2.text ="极高";
                    break;
                    case 1 : pinwei2.text ="较高";
                    break;
                    case 2 : pinwei2.text ="高";
                    break;
                    default: pinwei2.text ="默认";
                    break;
                    }
                }
            }
            Timer{
                id:aubuttontimer
                interval: 5000
                running: true///if not connect camera
                repeat: false
                onTriggered: {
                    aucamera.startaucamera()
                    aucameratimer.start()
                    auvaluetimer.start()
                }
            }

//            Button {
//                id: button1
//                text: "StartauCamera"
//                iconSource: qsTr("")
//                activeFocusOnPress: false
//                checked: false
//                anchors.left: parent.left
//                anchors.leftMargin: 0
//                anchors.top: parent.top
//                anchors.topMargin: 0
//                onClicked:{
//                    aucamera.startaucamera()
//                    aucameratimer.start()
//                    auvaluetimer.start()
//                }
//            }
            Text {
                id: autime
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
        id:aucharacter
        anchors.top:parent.top
        anchors.left: aucamerarec.right
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: "gray"
        Rectangle{
            anchors.fill: parent
        Column{
            anchors.top: parent.top
            id:aupinweiyuce
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
                id: aupinweiModel
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
                model: aupinweiModel
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

            anchors.top:aupinweiyuce.bottom
            width: parent.width
            height:18
            color: "#009090"
        }
        Column{
            anchors.top: aupinweiyuce.bottom
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
            id:autezheng
            width: parent.width
            height: (parent.height-75)/6
            color: "#000000"
           Text{
                id:aububblesize
                anchors.centerIn: parent
                text: "泡沫大小: " +imagevalue.auBubbleSize
                font.pixelSize:30
                font.italic: true
                color: "#00FF00"
            }
        }
        Rectangle{
            width: parent.width
            height: autezheng.height
            color: "#000000"
           Text{
                id:aububblenumber
                anchors.centerIn: parent
                text: "泡沫个数: "+imagevalue.auBubbleNumber
                font.pixelSize:30
                font.italic: true
                color: "#00FF00"
            }
        }
        Rectangle{
            width: parent.width
            height: autezheng.height
            color: "#000000"
           Text{
                id:augraymean
                anchors.centerIn: parent
                text: "泡沫颜色: "+imagevalue.auGrayMean
                font.pixelSize:30
                font.italic: true
                color: "#00FF00"
            }
        }
        Rectangle{
            width: parent.width
            height: autezheng.height
            color: "#000000"
           Text{
                id:aububblefangcha
                anchors.centerIn: parent
                text: "泡沫方差"
                font.pixelSize:30
                font.italic: true
                color: "#00FF00"
            }
        }
        Rectangle{
            width: parent.width
            height: autezheng.height
            color: "#000000"
           Text{
                id:auchengzailv
                anchors.centerIn: parent
                text: "承载率"
                font.pixelSize:30
                font.italic: true
                color: "#00FF00"
            }
        }
        Rectangle{
            width: parent.width
            height: autezheng.height
            color: "#000000"
           Text{
                id:aububblerate
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

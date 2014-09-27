//主界面，两个相机及其对应的加药


import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import AuCamera 1.0
import SbCamera 1.0

    Rectangle {
        id: rectangle1
        width: parent.width
        height: parent.height
        ColumnLayout {
            id: columnLayout1
            width: rectangle1.width*14/30
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
            anchors.top: parent.top
            anchors.topMargin: 8

            Rectangle {
                id: rectangle2
                height: rectangle1.height*14/30
                color: "#c92c2c"
                border.color: "#d2c1c1"
                anchors.right: parent.right
                anchors.rightMargin: 8
                anchors.left: parent.left
                anchors.leftMargin: 8
                anchors.top: parent.top
                anchors.topMargin: 8

                Rectangle {
                    id: rectangle6
                    height: rectangle1.height*12/30
                    color: "#ffffff"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                    AuCamera{
                        anchors.fill: parent
                        id: exaucamera
//                       renderTarget: FramebufferObject
                        Timer{
                            id: exaucameratimer
                            interval: 100
                            repeat: true
                            onTriggered: {
                                exautime.text = Date().toString()
                                exaucamera.getauimage()
                                exaucamera.updateaucamera()
                            }
                        }

//                        Button {
//                            id: exbutton1
//                            text: "StartauCamera"
//                            iconSource: qsTr("")
//                            activeFocusOnPress: false
//                            checked: false
//                            anchors.left: parent.left
//                            anchors.leftMargin: 0
//                            anchors.top: parent.top
//                            anchors.topMargin: 0
//                            onClicked:{
//                                exaucamera.startaucamera()
//                                exaucameratimer.start()
//                                exauvaluetimer.start()
//                            }
//                        }
                        Timer{
                            id:exaubuttontimer
                            interval: 7000
                            running: true///if not connect camera
                            repeat: false
                            onTriggered: {
                                exaucamera.startaucamera()
                                exaucameratimer.start()
                                      }
                        }
                        Text {
                            id: exautime
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

                Rectangle {
                    id: rectangle4
                    height: rectangle1.height/30
                    color: "#ffffff"
                    radius: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 40
                    anchors.left: parent.left
                    anchors.leftMargin: 40
                    anchors.top: parent.top
                    anchors.topMargin: 8

                    Text {
                        id: text1
                        color: "#f30707"
                        anchors.centerIn: parent
                        text: qsTr("金粗选槽视频")
                        font.pixelSize: 16
                    }
              }

            }

            Rectangle {
                id: rectangle3
                y: 362
                height: rectangle1.height*14/30
                color: "#c92c2c"
                anchors.right: parent.right
                anchors.rightMargin: 8
                anchors.left: parent.left
                anchors.leftMargin: 8
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 8
                Rectangle {
                    id: rectangle8
                    height: rectangle1.height*12/30
                    color: "#ffffff"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                    SbCamera{
                        anchors.fill: parent
                        id: exsbcamera
//                       renderTarget: FramebufferObject
                        Timer{
                            id: exsbameratimer
                            interval: 100
                            repeat: true
                            onTriggered: {
                                exsbtime.text = Date().toString()
                                exsbcamera.getsbimage()
                                exsbcamera.updatesbcamera()
                            }
                        }

//                        Button {
//                            id: exbutton2
//                            text: "StartauCamera"
//                            iconSource: qsTr("")
//                            activeFocusOnPress: false
//                            checked: false
//                            anchors.left: parent.left
//                            anchors.leftMargin: 0
//                            anchors.top: parent.top
//                            anchors.topMargin: 0
//                            onClicked:{
//                                exsbcamera.startsbcamera()
//                                exsbcameratimer.start()
//                                exsbvaluetimer.start()
//                            }
//                        }
                        Timer{
                            id:exsbbuttontimer
                            interval: 9000
                            running: true///if not connect camera
                            repeat: false
                            onTriggered: {
                                exsbcamera.startsbcamera()
                                exsbameratimer.start()
                            }
                        }
                        Text {
                            id: exsbtime
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
                }

            Rectangle {
                    id: rectangle5
                    height: rectangle1.height/30
                    color: "#ffffff"
                    radius: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 40
                    anchors.left: parent.left
                    anchors.leftMargin: 40
                    anchors.top: parent.top
                    anchors.topMargin: 8

                    Text {
                        id: text2
                        color: "#f30707"
                        anchors.centerIn: parent
                        text: qsTr("锑粗选槽视频")
                        font.pixelSize: 16
                    }
            }
        }


        ColumnLayout {
            id: columnLayout3
            anchors.left: columnLayout1.right
            anchors.rightMargin: 0
            anchors.right: columnLayout2.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
            anchors.top: parent.top
            anchors.topMargin: 8
            Rectangle{
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 8
                height: rectangle1.height*14/30
                Image {
                    id: arrow1
                    source: "arrow.png"
                    anchors.centerIn: parent
                }

            }
            Rectangle{
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.topMargin: 8
                height: rectangle1.height*14/30

                Image {
                    id: arrow2
                    source: "arrow.png"
                    anchors.centerIn: parent
                     }
            }


        }
        ColumnLayout {
            id: columnLayout2
            width: rectangle1.width*14/30
            anchors.right:  parent.right
            anchors.rightMargin: 8
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
            anchors.top: parent.top
            anchors.topMargin: 8
            Rectangle {
                id: rectangle9
                height: rectangle1.height*14/30
                color: "#c92c2c"
                border.color: "#d2c1c1"
                anchors.right: parent.right
                anchors.rightMargin: 8
                anchors.left: parent.left
                anchors.leftMargin: 8
                anchors.top: parent.top
                anchors.topMargin: 8

                Rectangle {
                    id: rectangle10
                    height: rectangle1.height*12/30
                    color: "#ffffff"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                    AuYaoji{

                    }
                }

                Rectangle {
                    id: rectangle11
                    height: rectangle1.height/30
                    color: "#ffffff"
                    radius: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 40
                    anchors.left: parent.left
                    anchors.leftMargin: 40
                    anchors.top: parent.top
                    anchors.topMargin: 8

                    Text {
                        id: text3
                        color: "#f30707"
                        anchors.centerIn: parent
                        text: qsTr("金粗选槽加药")
                        font.pixelSize: 16
                    }

            }

            }

            Rectangle {
                id: rectangle12
                y: 362
                height: rectangle1.height*14/30
                color: "#c92c2c"
                anchors.right: parent.right
                anchors.rightMargin: 8
                anchors.left: parent.left
                anchors.leftMargin: 8
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 8
                Rectangle {
                    id: rectangle13
                    height: rectangle1.height*12/30
                    color: "#ffffff"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                    SbYaoji{

                    }
                }
                Rectangle {
                    id: rectangle14
                    height: rectangle1.height/30
                    color: "#ffffff"
                    radius: 8
                    anchors.right: parent.right
                    anchors.rightMargin: 40
                    anchors.left: parent.left
                    anchors.leftMargin: 40
                    anchors.top: parent.top
                    anchors.topMargin: 8

                    Text {
                        id: text4
                        color: "#f30707"
                        anchors.centerIn: parent
                        text: qsTr("锑粗选槽加药")
                        font.pixelSize: 16
                    }
            }
        }

    }
    }


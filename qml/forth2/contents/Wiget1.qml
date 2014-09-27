//流程图和登陆界面


import QtQuick 2.0
import QtQuick.Dialogs 1.1
import QtQuick.Window 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
Rectangle {
    width:parent.width
    height:parent.height
    color:"transparent"

    Image
    {
        x: 20
        y: 0
        source:"forthprocess.jpg"

    }


    Image {
        id: image1
        anchors.right:parent.right
        anchors.rightMargin: 20
        y: 10
        source: "register_bg.png"
        MouseArea{
              anchors.fill: parent
              hoverEnabled :true
              onClicked:  {
                  loginwindow.visible=true
              }
          }

        AnimatedImage
        {
            id: pada
            fillMode:Image.PreserveAspectFit
            anchors.right: parent.right
            anchors.leftMargin: 20
            source: "panda.gif"
        }
        Text {
            anchors.left: parent.left
            anchors.leftMargin: 40
            anchors.top: parent.top
            anchors.topMargin: 10
            id: denglu
            text: "点我登录"
            font.pixelSize: 25
        }
        Window{
            id:loginwindow
            width: 320
            height: 240
            color: "#215400"
            visible: false
            Rectangle{
                anchors.fill: parent
                color: "#1d4d62"
                radius: 10
                border.color: "#000000"
                border.width: 2

                Rectangle {
                    id: rectangle1
                    x: 0
                    y: 1
                    width: 320
                    height: 42
                    color: "#c8c7c7"
                    radius: 9
                    border.width: 3
                    border.color: "#000000"

                    Text {
                        id: text1
                        x: 15
                        y: 8
                        width: 234
                        height: 26
                        text: "新龙矿业泡沫浮选系统"

                        font.bold: true

                        font.pixelSize: 26
                    }
                }

                Rectangle {
                    id: rectangle2
                    x: 8
                    y: 70
                    width: 304
                    height: 35
                    color: "#ffffff"
                    radius: 0
                    TextField {
                        id:textname
                        placeholderText: "请输入用户名"
                        Layout.fillWidth: true
                        anchors.fill: parent
                        font.pixelSize: 35

                    }
                   }

                Rectangle {
                    id: rectangle3
                    x: 8
                    y: 120
                    width: 304
                    height: 35
                    color: "#ffffff"
                    TextField {
                        id:textpassword
                        placeholderText: "请输入密码"
                        Layout.fillWidth: true
                        anchors.fill: parent
                        font.pixelSize: 35
                        echoMode: TextInput.Password
                    }
                }

                Button {
                    id: loginbutton
                    x: 8
                    y: 189
                    width: 304
                    height: 43
                    text: "登录"
                    onClicked: testid1()
                    function testid1()
                    {
                        if(textname.text=="csu"&&textpassword.text=="xks")
                        {
                            widget2.visible=true
                            widget3.visible=true
                            widget4.visible=true
                            widget5.visible=true
                            widget6.visible=true
                            widget7.visible=true
                            widget8.visible=true
                            loginresult.title="登陆成功"
                            loginresult.text="欢迎使用新龙矿业浮选系统"
                            loginresult.visible=true
                            loginwindow.visible=false
                            denglu.text="成功登录"
                             }
                        else{
                            loginresult.title="登陆失败"
                            loginresult.text="请重新登录"
                            loginresult.visible=true
                            loginresult.visible=false
                        }
                    }
                }
                MessageDialog{
                    id:loginresult
                    visible: false
                           }
            }
            }
    }
}

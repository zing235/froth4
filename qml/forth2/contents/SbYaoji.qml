import QtQuick 2.0
import QtQuick.Controls 1.1
Rectangle {
id:mainrec2
anchors.fill: parent
ListModel{
    id:dummyModel2
}
TableView{
    model: dummyModel2
    anchors.fill: parent
    TableViewColumn {
        id:yaojiname2
        role: "药剂名称"
        title: "药剂名称"
        width:mainrec2.width/3
    }
    TableViewColumn {
        id:zhidaovalue2
        role: "指导值"
        title: "指导值"
        width:mainrec2.width/3
    }
    TableViewColumn {
        id:yaojivalue2
        role: "当前值"
        title: "当前值"
        width: mainrec2.width/3
    }
    headerDelegate: BorderImage{// 标题托管
        source: "header.png"
        height: 30
        border{left:10;right:10;top:10;bottom:10}
        Text {
            text: styleData.value
            anchors.centerIn:parent
            color:"#000"
            font.pixelSize: 25
        }
    }
    itemDelegate: Item {//内容托管
        Text {
            anchors.centerIn: parent
            color: "#c92c2c"
            text: styleData.value
            font.pointSize: 20
            style: Text.Raised
            styleColor: "#AAAAAA"
            font.bold : true
             }
    }
    rowDelegate: Rectangle {//列托管
        height: (styleData.selected) ? 50 : 30
        Behavior on height{ NumberAnimation{} }
        color: styleData.selected ? "#448" : (styleData.alternate? "#eee" : "#fff")
        BorderImage{
            id: selected
            anchors.fill: parent
            source: "selectedrow.png"
            visible: styleData.selected
            border{left:2; right:2; top:2; bottom:2}
            SequentialAnimation {
                running: true; loops: Animation.Infinite
                NumberAnimation { target:selected; property: "opacity"; to: 1.0; duration: 900}
                NumberAnimation { target:selected; property: "opacity"; to: 0.5; duration: 900}
                            }
                        }
                    }
}
Timer{
    id: sqltimer2
    interval: 5100
    repeat: true
    running: true
    onTriggered: {
        imagevalue.updatesqlyaoji()
        dummyModel2.clear()
        dummyModel2.append({"药剂名称": "黑药",  "指导值": imagevalue.ZhidaoYaoji[0], "当前值": imagevalue.YaojiList[6]})
        dummyModel2.append({"药剂名称": "硫酸铜","指导值": imagevalue.ZhidaoYaoji[1], "当前值": imagevalue.YaojiList[7]})
        dummyModel2.append({"药剂名称": "硝酸铅","指导值": imagevalue.ZhidaoYaoji[2], "当前值": imagevalue.YaojiList[8]})
        dummyModel2.append({"药剂名称": "黄药",  "指导值": imagevalue.ZhidaoYaoji[3], "当前值": imagevalue.YaojiList[9]})
        dummyModel2.append({"药剂名称": "2号油", "指导值": imagevalue.ZhidaoYaoji[4], "当前值": imagevalue.YaojiList[10]})
    }
}

}

﻿import QtQuick
import QtQuick.Controls
import ChooseTheme
import "qrc:/CusWidgets" as CusWidgets

CusWidgets.Bubble {
  //自定义的弹窗，带三角尖尖的那个。
  id: skinBox
  barColor: ChooseTheme.reserverColor
  backgroundWidth: 320
  backgroundHeight: 175
  contentItem: GridView {
    anchors.fill: parent
    anchors.margins: 10
    model: ChooseTheme.themes
    cellWidth: 80
    cellHeight: 80
    clip: true
    delegate: Item {
      width: 80
      height: 80
      Rectangle {
        //表示主题色的色块
        anchors.fill: parent
        anchors.margins: 4
        height: width
        color: model.mainColor
      }
      Rectangle {
        //主题色边框，鼠标悬浮时显示
        anchors.fill: parent
        color: "transparent"
        border.color: model.mainColor
        border.width: 2
        visible: a.containsMouse
      }
      Text {
        //主题名字
        anchors {
          left: parent.left
          bottom: parent.bottom
          leftMargin: 8
          bottomMargin: 8
        }
        color: "white"
        text: model.name
      }
      Rectangle {
        //右下角圆圈圈，当前选中的主题
        x: parent.width - width
        y: parent.height - height
        width: 20
        height: width
        radius: width / 2
        color: model.mainColor
        border.width: 3
        border.color: ChooseTheme.reserverColor
        visible: ChooseTheme.currentTheme === index
      }
      MouseArea {
        //鼠标状态
        id: a
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
          //切主题操作
          ChooseTheme.currentTheme = index
        }
      }
    }
  }
}

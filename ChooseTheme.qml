pragma Singleton//声明该QML对象为单例

import QtQuick

QtObject {
  property color mainColor: "#eee"
  property color background: "#f9f9f9"
  property color selectedColor: "#d5d5d5"
  property color reserverColor: "#ffffff"
  property color textColor: "#555"
  property color splitColor: "gray"

  property int currentTheme: -1
  onCurrentThemeChanged: {
    var t = themes.get(currentTheme)
    mainColor = t.mainColor
    background = t.background
    textColor = t.textColor
    selectedColor = t.selectedColor
  }
  readonly property ListModel themes: ListModel {
    ListElement {
      name: qsTr("红")
      mainColor: "#da0606"
      background: "#fceaea"
      textColor: "#222"
      selectedColor: "#bf0404"
    }
    ListElement {
      name: qsTr("黑")
      mainColor: "#191b1f"
      background: "#222"
      textColor: "#f6f6f6"
      selectedColor: "#111"
    }
    ListElement {
      name: qsTr("粉")
      mainColor: "#faa0c5"
      background: "#fdf0f0"
      textColor: "#222"
      selectedColor: "#e999b4"
    }
    ListElement {
      name: qsTr("金")
      mainColor: "#fed98f"
      background: "#f9f8e0"
      textColor: "#222"
      selectedColor: "#efb336"
    }
    ListElement {
      name: qsTr("绿")
      mainColor: "#58c979"
      background: "#e2fcd8"
      textColor: "#222"
      selectedColor: "#46a757"
    }
    ListElement {
      name: qsTr("蓝")
      mainColor: "#67c1fd"
      background: "#d8f9fc"
      textColor: "#222"
      selectedColor: "#45a0db"
    }
  }
}

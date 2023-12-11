import QtQuick
import QtQuick.Controls

Rectangle {
  id: root

  signal accepted(string value)

  color: "#1e1e1e"
  border.color: searchInput.activeFocus ? Qt.lighter("#5F8575") : "transparent"
  border.width: 1

  TextInput {
    //文本输入框
    id: searchInput

    anchors.fill: parent

    font.pixelSize: 14
    color: "white"

    leftPadding: 30
    verticalAlignment: TextInput.AlignVCenter //顶部对齐

    Image {
      anchors {
        left: parent.left
        leftMargin: 5
        verticalCenter: parent.verticalCenter
      }

      width: 16
      height: 16

      mipmap: true //高清图像，可以优化图像的加载和显示效果
      source: "assets/icons/search_icon.png"
    }

    onAccepted: {
      root.accepted(text)
    }
  }
}

import QtQuick

Image {
  id: root

  signal clicked

  opacity: buttonMouseArea.containsMouse ? 0.75 : 1 //鼠标透明
  mipmap: true //改善图像在缩放时的显示效果的特性。

  fillMode: Image.PreserveAspectFit //保持纵横比
  MouseArea {
    id: buttonMouseArea

    anchors.fill: parent
    hoverEnabled: true

    onClicked: {
      root.clicked()
    }
  }
}

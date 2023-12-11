import QtQuick
import com.company.Playercontroller
import "qrc:/CusWidgets" as CusWidgets
import ChooseTheme

Rectangle {
  id: root

  property bool hidden: true

  signal searchRequested
  //搜索请求
  height: 400
  width: 250

  color: "#333333"

  Text {
    id: playlistText

    anchors {
      left: parent.left
      top: parent.top
      margins: 10
    }

    text: "歌曲列表"
    color: "white"
    font {
      bold: true
      pixelSize: 20
    }
  }

  ListView {
    id: listview

    anchors {
      top: playlistText.bottom
      bottom: addButton.top
      left: parent.left
      right: parent.right
      margins: 20
    }

    clip: true //超出矩形的部分将被剪切掉
    model: Playercontroller
    spacing: 10

    delegate: Rectangle {

      id: delegate

      required property string audioTitle
      required property string audioAuthorName
      required property url audioSource
      required property url audioImageSource
      required property url audioVideoSource
      required property int index

      width: listview.width
      height: 50

      color: "#1e1e1e"

      Column {
        id: textsColumn

        anchors {
          top: parent.top
          left: parent.left
          right: removeButton.left
          margins: 5
        }

        spacing: 5

        Text {
          //歌名
          width: textsColumn.width
          elide: Text.ElideRight
          fontSizeMode: Text.Fit
          minimumPixelSize: 10
          color: "white"
          text: delegate.audioTitle

          font {
            pixelSize: 14
            bold: true
          }
        }

        Text {
          //歌手
          width: textsColumn.width
          elide: Text.ElideRight//如果文本过长，会往右边进行省略
          fontSizeMode: Text.Fit//适应空间
          minimumPixelSize: 6
          color: "gray"
          text: delegate.audioAuthorName

          font {
            pixelSize: 10
          }
        }
      }

      MouseArea {
        //点击索引
        id: delegateMouseArea

        anchors.fill: parent

        onClicked: {
          Playercontroller.switchToAudioByIndex(delegate.index)
        }
      }

      ImageButton {
        //移除
        id: removeButton

        anchors {
          right: parent.right
          verticalCenter: parent.verticalCenter
          rightMargin: 5
        }

        width: 30
        height: 30

        source: "assets/icons/trash_icon.png"

        onClicked: {
          Playercontroller.removeAudio(delegate.index)
        }
      }
    }
  }

  ImageButton {
    id: addButton

    anchors {
      left: parent.left
      bottom: parent.bottom
      margins: 20
    }

    source: "assets/icons/add_icon.png"

    width: 32
    height: 32

    onClicked: {
      root.searchRequested()
      root.hidden = true
    }
  }
  Behavior on x {
    //通过将这个行为应用到一个具有x属性的元素上，当x属性发生变化时，将会应用这个动画效果
    PropertyAnimation {
      easing.type: Easing.InOutQuad
      duration: 200
    }
  }
}

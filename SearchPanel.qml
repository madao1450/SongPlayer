﻿import QtQuick
import com.company.Playercontroller
import com.company.AudioSearchModel


Rectangle {
  id: root

  property bool hidden: true

  color: "#333333"

  ListView {
    //列表视图
    id: listView

    anchors {
      fill: parent
      margins: 20
    }

    spacing: 10
    clip: true
    model: AudioSearchModel
    visible: !AudioSearchModel.isSearching
    delegate: Rectangle {
      id: delegate
      //必要属性
      required property string audioName
      required property string audioAuthor
      required property url audioImageSource
      required property url audioSource
      required property int index

      width: listView.width
      height: 50

      color: "#1e1e1e"

      Image {
        id: audioImage

        anchors {
          left: parent.left
          leftMargin: 5
          verticalCenter: parent.verticalCenter
        }

        width: 32
        height: 32

        source: delegate.audioImageSource
      }

      Column {
        anchors {
          left: audioImage.right
          right: parent.right
          top: parent.top

          margins: 5
        }

        spacing: 5

        Text {
          width: parent.width

          text: delegate.audioName
          color: "white"

          fontSizeMode: Text.Fit //这将Text的字体大小设置为适合其宽度，不会换行
          minimumPixelSize: 12
          elide: Text.ElideRight //右省略

          font {
            pixelSize: 16
            bold: true
          }
        }

        Text {
          width: parent.width

          text: delegate.audioAuthor
          color: "gray"

          fontSizeMode: Text.Fit
          minimumPixelSize: 8
          elide: Text.ElideRight

          font {
            pixelSize: 12
          }
        }
      }

      MouseArea {
        anchors.fill: parent

        onClicked: {
          root.hidden = true
          Playercontroller.addAudio(delegate.audioName, delegate.audioAuthor,
                                    delegate.audioSource,
                                    delegate.audioImageSource)
        }
      }
    }
  }

  Text {
    anchors.centerIn: parent

    color: "gray"
    visible: AudioSearchModel.isSearching || listView.count === 0//text属性是否可见
    text: if (AudioSearchModel.isSearching) {
            return "Searching..."
          } else if (listView.count === 0) {
            return "No results"
          } else {
            return ""
          }

    font {
      pixelSize: 24
      bold: true
    }
  }

  Behavior on y {
    PropertyAnimation {
      easing.type: Easing.InOutQuad
      duration: 200
    }
  }
}
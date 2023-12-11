import QtQuick
import QtMultimedia
import com.company.Playercontroller

Item {
  id: root

  Image {
    id: albumImage

    anchors {
      verticalCenter: parent.verticalCenter //中心
      left: parent.left
    }
    width: 150
    height: 150

    source: !!Playercontroller.currentSong ? Playercontroller.currentSong.imageSource : "" //显示图片
    //图片旋转
    NumberAnimation on x {

      to: 900
      duration: 10000
      loops: Animation.Infinite
    }
    RotationAnimation on rotation {

      to: 900
      duration: 10000
      loops: Animation.Infinite
    }
  }
  //声源
  Video {
    id: albumVideo

    anchors {
      verticalCenter: parent.verticalCenter //对齐
      left: parent.left
    }
    width: 150
    height: 150

    loops: MediaPlayer.Infinite
    volume: 0

    source: !!Playercontroller.currentSong ? Playercontroller.currentSong.videoSource : ""

    onSourceChanged: {
      if (source != "") {
        play()
      } else {
        stop()
      }
    }
  }
  //歌名
  Text {
    id: titleText

    anchors {
      bottom: parent.verticalCenter
      left: albumImage.right
      margins: 20
      right: parent.right
    }
    color: "white"
    wrapMode: Text.WrapAtWordBoundaryOrAnywhere //设置文本的换行模式，自动换行
    text: !!Playercontroller.currentSong ? Playercontroller.currentSong.title : ""

    font {
      pixelSize: 20
      bold: true //粗体
    }
  }
  //作者
  Text {
    id: authorText

    anchors {
      top: parent.verticalCenter
      left: titleText.left
      topMargin: 5
      right: parent.right
    }
    color: "gray"
    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
    text: !!Playercontroller.currentSong ? Playercontroller.currentSong.authorName : ""

    font {
      pixelSize: 16
    }
  }
}

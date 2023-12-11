import QtQuick
import QtQuick.Controls
import QtQuick.Window
import com.company.Playercontroller
import com.company.AudioSearchModel
import "qrc:/CusWidgets" as CusWidgets
import ChooseTheme
import QtMultimedia

Window {
  id: root

  width: 480
  height: 640
  visible: true
  title: "Song Player"

  Rectangle {
    id: topbar

    anchors {
      top: parent.top
      left: parent.left
      right: parent.right
    }

    height: 50

    //color: "#5F8575"
    color: CusWidgets.ImageButton.pressed ? Qt.darker(
                                              ChooseTheme.mainColor,
                                              1.1) : ChooseTheme.mainColor
    SearchField {
      anchors {
        left: parent.left
        right: closeSearchButton.left
        verticalCenter: parent.verticalCenter
        margins: 10 //设置控件的边框到另一个控件的边框的距离的属性，属于容器外部距离
      }

      height: 30

      visible: !searchPanel.hidden
      enabled: !AudioSearchModel.isSearching

      onAccepted: value => {
                    AudioSearchModel.searchSong(value)
                    topbar.forceActiveFocus()
                  }
    }

    CusWidgets.ImageButton {
      source: "qrc:/assets/icons/skin_icon.png"
      imageColor: "#ccc"
      imageHoverColor: "#00FFFF"
      imagePadding: 8
      width: 32
      height: 32
      anchors {
        right: playlistIcon.left
        verticalCenter: parent.verticalCenter
        rightMargin: 20
      }
      onClicked: {
        if (skinpopWin.popupVisible === true) {
          skinpopWin.hide()
        } else {
          skinpopWin.show()
        }
      }

      PopUp {
        id: skinpopWin
      }
    }

    ImageButton {
      id: playlistIcon

      anchors {
        right: parent.right
        verticalCenter: parent.verticalCenter
        rightMargin: 20
      }

      width: 32
      height: 32
      source: "assets/icons/menu_icon.png"

      visible: searchPanel.hidden

      onClicked: {
        playlistPanel.hidden = !playlistPanel.hidden
      }
    }

    ImageButton {
      id: closeSearchButton

      anchors {
        right: parent.right
        verticalCenter: parent.verticalCenter
        rightMargin: 20
      }

      height: 32
      width: 32

      source: "assets/icons/close_icon.png"
      visible: !searchPanel.hidden

      onClicked: {
        searchPanel.hidden = true
      }
    }
  }

  Rectangle {
    id: mainSection

    anchors {
      top: topbar.bottom
      bottom: bottomBar.top
      left: parent.left
      right: parent.right
    }
    // color: "#1e1e1e"
    color: CusWidgets.ImageButton.pressed ? Qt.darker(
                                              ChooseTheme.background,
                                              1.1) : ChooseTheme.background

    AudioInfoBox {
      id: firstSong

      anchors {
        left: parent.left
        right: parent.right
        verticalCenter: parent.verticalCenter
        margins: 20
      }
    }
  }

  Rectangle {
    id: bottomBar

    anchors {
      bottom: parent.bottom
      left: parent.left
      right: parent.right
    }

    height: 100

    color: CusWidgets.ImageButton.pressed ? Qt.darker(
                                              ChooseTheme.mainColor,
                                              1.1) : ChooseTheme.mainColor

    Row {
      anchors.centerIn: parent

      spacing: 20 //设置自身边框到自身内部另一个容器边框之间的距离的属性，属于容器内距离
      enabled: !!Playercontroller.currentSong
      opacity: enabled ? 1 : 0.3

      ImageButton {
        id: previousButton

        anchors.verticalCenter: parent.verticalCenter
        width: 30
        height: 30

        source: "assets/icons/previous_icon.png"

        onClicked: Playercontroller.switchToPreviousSong()
      }

      ImageButton {
        id: playPauseButton

        anchors.verticalCenter: parent.verticalCenter
        width: 50
        height: 50

        source: Playercontroller.playing ? "assets/icons/pause_icon.png" : "assets/icons/play_icon.png"

        onClicked: Playercontroller.playPause()
      }

      ImageButton {
        id: nextButton

        anchors.verticalCenter: parent.verticalCenter
        width: 30
        height: 30

        source: "assets/icons/next_icon.png"

        onClicked: Playercontroller.switchToNextSong()
      }
    }
  }
  PlaylistPanel {
    id: playlistPanel

    anchors {
      top: topbar.bottom
    }

    x: hidden ? parent.width : parent.width - width
    onSearchRequested: {
      searchPanel.hidden = false
    }
  }

  SearchPanel {
    id: searchPanel

    anchors {
      left: parent.left
      right: parent.right
    }

    height: mainSection.height + bottomBar.height

    y: hidden ? parent.height : topbar.height
  }

  MediaPlayer {
    id: musicPlayer

    onSourceChanged: {
      musicPlayer.play()
    }
  }

}

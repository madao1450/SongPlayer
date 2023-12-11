cmake_minimum_required(VERSION 3.16)

project(SongPlayer VERSION 0.1 LANGUAGES CXX)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Multimedia )

qt_standard_project_setup()

qt_add_executable(appSongPlayer
    main.cpp  Playercontroller.cpp Playercontroller.h   AudioSearchModel.cpp AudioSearchModel.h   qml.qrc  ${TaoQuickRes}
)

qt_add_qml_module(appSongPlayer
    URI SongPlayer
    VERSION 1.0
    QML_FILES Main.qml  AudioInfoBox.qml ImageButton.qml    PlaylistPanel.qml  SearchField.qml SearchPanel.qml
           PopUp.qml


   SOURCES
   Audioinfo.cpp Audioinfo.h

    RESOURCES

    assets/images/OIP.jpg
assets/images/song.jpg
assets/images/sing.jpg

    assets/icons/many.png
    assets/icons/nextSong.png
    assets/icons/previousSong.png
     assets/icons/pause.png
     assets/icons/add_icon.png
    assets/icons/audio.ico
     assets/icons/trash_icon.png
     assets/icons/menu_icon.png
     assets/icons/play_icon.png
    assets/icons/previous_icon.png
    assets/icons/pause_icon.png
    assets/icons/next_icon.png
    assets/icons/close_icon.png
    assets/icons/search_icon.png
     assets/icons/skin_icon.png
     assets/icons/volume.png

    assets/audio/Anthem_Lights_-_Love_You_Like_the_Movies.mp3
   assets/audio/JVKE_-_golden_hour.mp3
   assets/audio/Jake_Miller__Jabbar_Hakeem.mp3



)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appSongPlayer PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appSongPlayer
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appSongPlayer
    PRIVATE Qt6::Quick     Qt6::Multimedia
)

include(GNUInstallDirs)
install(TARGETS appSongPlayer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

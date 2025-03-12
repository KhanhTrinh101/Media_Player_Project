import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1

Drawer {
    id: drawerId
    interactive: false
    modal: false
    background: Rectangle {
        id: playList_bg
        anchors.fill: parent
        color: "transparent"
    }

    property string notify: "Notify"

    property string mediaPlayList_bg: "qrc:/images/back ground/playlist.png"
    property string playList_HoldBg: "qrc:/images/back ground/hold.png"
    property string playList_item: "qrc:/images/back ground/playlist_item.png"

    // List Songs
    ListView {
        id: mediaPlaylist
        anchors.fill: parent
        model: playlistModel
        clip: true
        spacing: 2
        currentIndex: 0
        delegate: MouseArea {
            property variant myData: model
            implicitWidth: playlistItem.width
            implicitHeight: playlistItem.height

            Image {
                id: playlistItem
                width: mediaPlaylist.width
                height: mediaPlaylist.height / 6
                source: mediaPlayList_bg
                opacity: 0.5
            }

            Text {
                text: title
                anchors.fill: parent
                anchors.leftMargin: mediaPlaylist.width / 7
                verticalAlignment: Text.AlignVCenter
                color: "white"
                font.pixelSize: playlistItem.height / 4.5
            }

            // onClicked: {
            //     player.playlist.setCurrentIndex(index)
            // }

            onPressed: {
                playlistItem.source = playList_HoldBg
            }

            onReleased: {
                playlistItem.source = mediaPlayList_bg
            }

            onCanceled:  {
                playlistItem.source = mediaPlayList_bg
            }
        }

        // Notify will show when list songs is empty
        Text {            
            anchors.horizontalCenter: parent.horizontalCenter   
            text: notify
            color: "white"
            font.pointSize: headerItem.height / 9
            visible: mediaPlaylist.count ? false : true
        }

        highlight: Image {
            source: playList_item
            width: mediaPlaylist.width
            height: mediaPlaylist.height / 6

            Image {
                source: playList_item
                anchors.left: parent.left
                anchors.leftMargin: width / 2
                anchors.verticalCenter: parent.verticalCenter
                width: headerItem.height * 0.3
                height: width
            }
        }

        ScrollBar.vertical: ScrollBar {
            parent: mediaPlaylist.parent
            anchors.top: mediaPlaylist.top
            anchors.left: mediaPlaylist.right
            anchors.bottom: mediaPlaylist.bottom
        }
    }

    // Connections{
    //     target: PlayList
    //     onCurrentIndexChanged: {
    //         mediaPlaylist.currentIndex = index;
    //     }
    // }
}

import QtQuick 2.0

Item {
    property string playlist_Str: "Play List"
    property string header_Str: "Header Tittle"

    property string headerItem_bg: "qrc:/images/back ground/title.png"
    property string buttonDraw_iconOff: "qrc:/images/icon/drawer_p.png"
    property string buttonDraw_iconOn: "qrc:/images/icon/back.png"

    Image {
        id: headerItem
        anchors.fill: parent
        source: headerItem_bg

        // Button drawer
        SwitchButton {
            id: playlist_button
            heihgtSize: parent.height / 3
            widthSize: heihgtSize
            anchors.left: parent.left
            anchors.leftMargin: widthSize / 2
            anchors.verticalCenter: parent.verticalCenter
            icon_off:buttonDraw_iconOff
            icon_on: buttonDraw_iconOn
            // onStatusChanged: {
            //     if(playlist_button.status === 1) {
            //         playlist.open()
            //     } else {
            //         playlist.close()
            //     }
            // }
        }

        // text playlist
        Text {
            anchors.left: playlist_button.right
            anchors.leftMargin: playlist_button.heihgtSize / 2
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            text: playlist_Str
            color: "white"
            font.pixelSize: parent.height / 4
        }

        // text media
        Text {
            id: headerTitleText
            text: header_Str
            anchors.centerIn: parent
            color: "white"
            font.pixelSize: parent.height / 3
        }

        // // VietNam Flag
        // Image {
        //     id: vn_flag
        //     anchors.right: parent.right
        //     anchors.rightMargin: playlist_button.heihgtSize
        //     anchors.verticalCenter: parent.verticalCenter
        //     width: playlist_button.heihgtSize
        //     height: playlist_button.heihgtSize
        //     source: "qrc:/images/icon/vn.png"

        //     property bool click_vn_flag: false

        //     Rectangle{
        //         width: parent.width
        //         height: width / 1.5
        //         anchors.verticalCenter: parent.verticalCenter
        //         border.color: "blue"
        //         border.width: 3
        //         color: "transparent"
        //         visible: vn_flag.click_vn_flag ? true : false
        //     }

        //     MouseArea {
        //         anchors.fill: parent
        //         onClicked: {
        //             // Translator.selectLanguage("vn")
        //             vn_flag.click_vn_flag = true
        //             us_flag.click_us_flag = false
        //         }
        //     }
        // }

        // // America Flag
        // Image {
        //     id: us_flag
        //     anchors.right: vn_flag.left
        //     anchors.rightMargin: 10
        //     anchors.verticalCenter: parent.verticalCenter
        //     width: vn_flag.width
        //     height: vn_flag.width
        //     source: "qrc:/images/icon/us.png"
        //     property bool click_us_flag: true
        //     Rectangle{
        //         width: parent.width
        //         height: width / 1.5
        //         anchors.verticalCenter: parent.verticalCenter
        //         border.color: "blue"
        //         border.width: 3
        //         color: "transparent"
        //         visible: us_flag.click_us_flag ? true : false
        //     }
        //     MouseArea {
        //         anchors.fill: parent
        //         onClicked: {
        //             // Translator.selectLanguage("us")
        //             // us_flag.click_us_flag = true
        //             // vn_flag.click_vn_flag = false
        //         }
        //     }
        // }
    }
}

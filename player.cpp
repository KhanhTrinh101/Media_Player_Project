/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "player.h"
#include "playlistmodel.h"
// #include <QMediaService>
// #include <QMediaPlaylist>
#include <QMediaMetaData>
#include <QObject>
#include <QFileInfo>
#include <QTime>
#include <QDir>
#include <QStandardPaths>

Player::Player(QObject *parent)
    : QObject(parent)
{
    m_player = new QMediaPlayer(this);
    m_playlist = new QString();
    m_playlistModel = new PlaylistModel(this);
    open();

    // if(getPlaylist() != NULL)
    //     m_player->setPlaylist(m_playlist);

    // if (!m_playlist->isEmpty())
    //     m_playlist->setCurrentIndex(0);
}

Player::~Player()
{
    if(m_player != NULL)
    {
        delete m_player;
    }

    if(m_playlist != NULL)
    {
        m_playlist = NULL;
    }

    if(m_playlistModel != NULL)
    {
        delete m_playlistModel;
    }
}

/*
 * bref: load file .mp3 from music location
 */
void Player::open()
{
    QList<QUrl> urls;

    /* Read the url which is readed from music localtion */
    QStringList musicLocalPath = QStandardPaths::standardLocations(QStandardPaths::MusicLocation);
    QDir directory(musicLocalPath[0]);
    QFileInfoList musics = directory.entryInfoList(QStringList() << "*.mp3", QDir::Files);

    /* Add the url to list urls which is readed from music localtion */
    for (int index = 0; index < musics.length(); index++)
    {
        urls.append(QUrl::fromLocalFile(musics[index].absoluteFilePath()));
        qDebug() << urls[index].toString();
    }

    addUrlToPlaylist(urls);
}

/*
 * bref: Add song to the play list songs
 */
void Player::addUrlToPlaylist(const QList<QUrl> &urls)
{
    int index = 0;
    QString artSong = NULL;
    FileRef file;
    Tag *tag = NULL;

    for (auto &url: urls)
    {
        /* Add url to list url */
        m_playlist[index] = url.toString();

        /* Get album art from url */
        artSong = getAlbumArt(url);

        /* Get title and artist from url */
        file = FileRef(url.toLocalFile().toStdString().c_str());
        tag = file.tag();

        /* Add song to the play list songs */
        Song song(QString::fromWCharArray(tag->title().toCWString()), QString::fromWCharArray(tag->artist().toCWString()), url.toDisplayString(), artSong);
        m_playlistModel->addSong(song);

        index++;
    }
}

/*
 * bref: covert thời gian từ millisecond sang giờ phút giây
 */
QString Player::getTimeInfo(qint64 currentInfo)
{
    QString tStr = "00:00";
    currentInfo = currentInfo/1000;
    qint64 durarion = m_player->duration()/1000;

    if (currentInfo || durarion)
    {
        QTime currentTime((currentInfo / 3600) % 60, (currentInfo / 60) % 60,
                          currentInfo % 60, (currentInfo * 1000) % 1000);
        QTime totalTime((durarion / 3600) % 60, (m_player->duration() / 60) % 60,
                        durarion % 60, (m_player->duration() * 1000) % 1000);
        QString format = "mm:ss";

        if (durarion > 3600)
        {
            format = "hh::mm:ss";
        }
        tStr = currentTime.toString(format);
    }

    return tStr;
}

// // điều khiển các trạng thái chơi của các bài hát
// void Player::playBackModeList(QMediaPlaylist::PlaybackMode mode)
// {
//     // chơi ngẫu nhiên
//     if(mode == QMediaPlaylist::Random)
//         m_playlist->setPlaybackMode(QMediaPlaylist::Random);
//     // chơi lập lại một bài hát
//     else if(mode == QMediaPlaylist::CurrentItemInLoop)
//         m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
//     // chơi bình thường
//     else if(mode == QMediaPlaylist::Sequential)
//         m_playlist->setPlaybackMode(QMediaPlaylist::Sequential);
//     else
//         qDebug() << "NOT AVAILABLE MODE!!!";

// }

QMediaPlayer *Player::getPlayer()
{
    return m_player;
}

QString *Player::getPlaylist()
{
    return m_playlist;
}

PlaylistModel *Player::getPlaylistModel()
{
    return m_playlistModel;
}

// trích xuất album art của bài hát
QString Player::getAlbumArt(QUrl url)
{
    TagLib::MPEG::File mpegFile(url.toLocalFile().toStdString().c_str());
    TagLib::ID3v2::FrameList Frame ;
    TagLib::ID3v2::AttachedPictureFrame *PicFrame ;
    void *SrcImage ;
    unsigned long Size ;
    FILE *jpegFile;
    jpegFile = fopen(QString(url.fileName()+".jpg").toStdString().c_str(),"wb");

    // kiển tra xem có tag tồn tại không
    if ( mpegFile.ID3v2Tag() )
    {
        Frame = mpegFile.ID3v2Tag()->frameListMap()["APIC"];

        if (!Frame.isEmpty() )
        {
            for(TagLib::ID3v2::FrameList::ConstIterator it = Frame.begin(); it != Frame.end(); ++it)
            {
                PicFrame = static_cast<TagLib::ID3v2::AttachedPictureFrame*>(*it) ;

                if ( PicFrame->type() == TagLib::ID3v2::AttachedPictureFrame::FrontCover)
                {
                    Size = PicFrame->picture().size();
                    SrcImage = malloc ( Size );

                    if ( SrcImage )
                    {
                        memcpy ( SrcImage, PicFrame->picture().data(), Size );
                        fwrite(SrcImage,Size,1, jpegFile);
                        fclose(jpegFile);
                        free( SrcImage);
                        qDebug() << QUrl::fromLocalFile(url.fileName()+".jpg").toDisplayString();
                        return QUrl::fromLocalFile(url.fileName()+".jpg").toDisplayString();
                    }
                }
            }
        }
    }
    else
    {
        qDebug() <<"id3v2 not present";
        return "qrc:/images/back ground/album_art.png";
    }
    return "qrc:/images/back ground/album_art.png";
}

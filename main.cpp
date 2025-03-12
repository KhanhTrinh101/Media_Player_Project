#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "player.h"
#include <QQmlContext>
#include "playlistmodel.h"
#include <QMediaPlayer>
// #include <QMediaPlaylist>
#include <QMetaType>
#include "translator.h"

int main(int argc, char *argv[])
{
    // QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // qRegisterMetaType<QMediaPlaylist*>("QMediaPlaylist*");
    // qRegisterMetaType<QMediaPlaylist::PlaybackMode>("QMediaPlaylist::PlaybackMode");

    QGuiApplication app(argc, argv);

    // app.setOrganizationName("Some Company");
    // app.setOrganizationDomain("somecompany.com");
    // app.setApplicationName("Amazing Application");

    QQmlApplicationEngine engine;

    // Translator translator;
    // if(translator.currentLanguage() != QString())
    // {
    //     translator.setCurrentLanguage("us");
    //     engine.rootContext()->setContextProperty("Translator", &translator);
    // }

    Player player;
    // engine.rootContext()->setContextProperty("APP_CTRL", &player);

    // /* Set player object to player variable */
    // if(player.getPlayer() != NULL)
    // {
    //     engine.rootContext()->setContextProperty("player", player.getPlayer());
    // }
    // else
    // {
    //     qDebug() << "Can't get player!";
    // }

    // /* Set list model object to play list model variable */
    if( player.getPlaylistModel() != NULL)
    {
        engine.rootContext()->setContextProperty("playlistModel", player.getPlaylistModel());
    }
    // else
    // {
    //     qDebug() << "Can't get play list model!";
    // }

    // if(player.getPlaylist() != NULL)
    //     engine.rootContext()->setContextProperty("PlayList", *(player.getPlaylist()));
    // else
    //     qDebug() << "QmediaPlaylist is NULL";

    // engine.rootContext()->setContextProperty("utility", &player);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

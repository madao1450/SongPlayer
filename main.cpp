#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include"Playercontroller.h"
#include "AudioSearchModel.h"
#include <QQmlContext>
#include"Playercontroller.h"

int main(int argc, char *argv[])
{
     QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

     app.setWindowIcon(QIcon(":/SongPlayer/assets/icons/audio.ico"));


    QQmlApplicationEngine engine;


     qmlRegisterSingletonType(QUrl("qrc:/ChooseTheme.qml"), "ChooseTheme", 1, 0, "ChooseTheme");//注册QML单例类型

     Playercontroller *playerController = new Playercontroller(&app);
     qmlRegisterSingletonInstance("com.company.Playercontroller",1,0, "Playercontroller",playerController);//用于注册已经存在的对象的单例实例
     
     AudioSearchModel *audioSearchModel = new AudioSearchModel(&app);
     qmlRegisterSingletonInstance("com.company.AudioSearchModel",1,0,"AudioSearchModel",audioSearchModel);

    const QUrl url(u"qrc:/SongPlayer/Main.qml"_qs);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

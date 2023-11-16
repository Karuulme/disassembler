#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
//#include <Header/readpefile.h>
#include <Header/resolvent.h>
//#include <Header/define.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
   // ReadPeFile * readPeFile;
    Resolvent   resolvent;

   // Object::connect(readPeFile,SIGNAL(setTextData(TextSection)),resolvent, SLOT(getTextData(TextSection)));
    //const QUrl url("qrc:///main.qml");
    const QUrl url("qrc:/main.qml");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}

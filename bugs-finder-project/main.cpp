#include "gl-engine/renderer.h"

#include <QGuiApplication>
#include <QtQml>
#include <QSharedPointer>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<Renderer>("OpenGLEngine", 1, 0, "AnimationRenderer");

    engine.load(QUrl("qrc:/qml/main.qml"));

    return a.exec();
}


#include "Core.hpp"
#include "include/App.hpp"
#include "include/UIDistortionPedal.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    qmlRegisterType<UIDistortionPedal>("Pedals", 1, 0, "UIDistortionPedal");

    std::shared_ptr<Core> core = std::make_shared<Core>(
        "/Users/yasha_nev/Projects/virtualGuitarPedalBoard/build/plugins");

    engine.rootContext()->setContextProperty("app", new App(core));

    engine.loadFromModule("vgpUI", "Main");

    return app.exec();
}

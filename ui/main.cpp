#include "Core.hpp"
#include "include/App.hpp"
#include "include/UIChorusPedal.hpp"
#include "include/UIDelayPedal.hpp"
#include "include/UIDistortionPedal.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char* argv[]) {

    if(argc < 2) {
        std::cout << "Usege: vgp path/to/plugins/dir\n";
        return 0;
    }

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    qmlRegisterType<UIDistortionPedal>("Pedals", 1, 0, "UIDistortionPedal");
    qmlRegisterType<UIDelayPedal>("Pedals", 1, 0, "UIDelayPedal");
    qmlRegisterType<UIChorusPedal>("Pedals", 1, 0, "UIChorusPedal");

    std::shared_ptr<Core> core = std::make_shared<Core>(argv[1]);

    engine.rootContext()->setContextProperty("app", new App(core));

    engine.loadFromModule("vgpUI", "Main");

    return app.exec();
}

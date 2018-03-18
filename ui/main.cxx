#include <ui/backend/Launcher.hxx>
#include <ui/backend/TypeRegistrator.hxx>

#include <QQmlEngine>
#include <QQuickView>
#include <QtGui/QGuiApplication>

#include <gum/log/LoggerManager.h>
#include <gum/log/sinks/AnsiTerminalLoggerSink.h>

using namespace ui;

int main(int argc, char** argv) {
    gum::Token terminalLoggerConnection = gum::LoggerManager::get().register_logger_sink(gum::make_shared_ref<gum::AnsiTerminalLoggerSink>());

    QGuiApplication app(argc, argv);

    QQuickView mainView;
    QQmlEngine& qmlEngine = *mainView.engine();
    QObject::connect(&qmlEngine, &QQmlEngine::quit, &app, &QGuiApplication::quit);

    TypeRegistrator typeRegistrator;

    const UiContextRef uiContext = gum::make_shared_ref<UiContext>();
    Launcher launcher(qmlEngine, uiContext);

    mainView.setSource(QUrl::fromLocalFile(":/qml/Main.qml"));
    mainView.show();

    return app.exec();
}

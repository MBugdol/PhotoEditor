#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QScopedPointer>

#include "src/EditedImageProvider.h"
#include "src/PhotoEditor.h"

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    //configure image provider
    QScopedPointer<EditedImageProvider> img_provider(new EditedImageProvider);
    engine.rootContext()->setContextProperty("editorimg", img_provider.get());
    engine.addImageProvider("editorimg", img_provider.get());
    //configure PhotoEditor qml interface
    QScopedPointer<PhotoEditor> photo_editor(new PhotoEditor);
    engine.rootContext()->setContextProperty("editor", photo_editor.get());

    //create necessary connections
    QObject::connect(photo_editor.get(), &PhotoEditor::previewUpdated, img_provider.get(), &EditedImageProvider::updatePreview);
    QObject::connect(photo_editor.get(), &PhotoEditor::currentUpdated, img_provider.get(), &EditedImageProvider::updateCurrent);

    //load main.qml into engine
    const QUrl url(u"qrc:/PhotoEditor/qml/main.qml"_qs);
    engine.load(url);
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}

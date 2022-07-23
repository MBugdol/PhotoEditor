#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "src/PhotoEditor.h"
#include "src/EditedImageProvider.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    EditedImageProvider* img_provider = new EditedImageProvider;
    engine.rootContext()->setContextProperty("editorimg", img_provider);
    engine.addImageProvider(QString("editorimg"), img_provider);
    PhotoEditor* photo_editor = new PhotoEditor;
    engine.rootContext()->setContextProperty("editor", photo_editor);

    QObject::connect(photo_editor, &PhotoEditor::previewUpdated, img_provider, &EditedImageProvider::updatePreview);
    QObject::connect(photo_editor, &PhotoEditor::currentUpdated, img_provider, &EditedImageProvider::updateCurrent);

    engine.load("main.qml");
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}

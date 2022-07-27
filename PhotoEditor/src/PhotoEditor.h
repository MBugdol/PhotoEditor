#pragma once

#include <QObject>
#include <QImage>
#include <QUrl>
#include <QUndoStack>
#include <QUndoCommand>
#include <QStack>
#include "src/PhotoEditionCommands.h"

class PhotoEditor : public QObject
{
    Q_OBJECT
public:
    enum class Actions {
        Rotate,
        Flip,
        Scale,
        Grayscale,
        Hue,
        ResetColor
    };
    explicit PhotoEditor(QObject* parent = nullptr);
    void update();
signals:
    void previewUpdated(const QImage& updated_preview);
    void currentUpdated(const QImage& updated_current);
    void historyUpdated();
public slots:
    void loadFromUrl(const QUrl& url);
    void saveToUrl(const QUrl& url);

    PhotoEditCommand* createAction(QString action, QStringList args);

    QList<QObject*> history();
    void remove(int index);
    void swap(int index1, int index2);

    void execute(PhotoEditCommand* action);
    void approveChanges();
    void undo();
    void redo();

    PhotoEditCommand* rotation(qreal angle);
    PhotoEditCommand* flip(QString orientation);
    PhotoEditCommand* scale(int width, int height);
    PhotoEditCommand* grayscale();
    PhotoEditCommand* hueShift(int hue);
    PhotoEditCommand* resetColorChannel(QString channel);


private:
    QImage m_original_image;
    QImage m_preview_image;
    QImage m_current_image;

    QUndoStack m_actions;
    PhotoEditCommand* m_current_action = 0;
};

#include "PhotoEditor.h"
#include <QTransform>
#include <QVariant>
#include <QHash>

PhotoEditor::PhotoEditor(QObject *parent)
    : QObject(parent), m_current_action(0) {}
void PhotoEditor::update() {
    m_preview_image = m_current_image;
    emit previewUpdated(m_preview_image);
    emit currentUpdated(m_current_image);
    emit historyUpdated();
}

void PhotoEditor::loadFromUrl(const QUrl& url) {
    m_actions.clear();
    m_original_image = m_preview_image = m_current_image = QImage(url.toLocalFile());
    emit previewUpdated(m_preview_image);
    emit currentUpdated(m_current_image);
}
void PhotoEditor::saveToUrl(const QUrl& url) {
    m_current_image.save(url.toLocalFile());
}

PhotoEditCommand* PhotoEditor::createAction(QString action, QStringList args) {
    QHash<QString, PhotoEditor::Actions> translate{
        {"rotate", PhotoEditor::Actions::Rotate},
        {"flip", PhotoEditor::Actions::Flip},
        {"scale", PhotoEditor::Actions::Scale},
        {"grayscale", PhotoEditor::Actions::Grayscale},
        {"hue", PhotoEditor::Actions::Hue},
        {"reset color", PhotoEditor::Actions::ResetColor}
    };
    PhotoEditor::Actions action_enum = translate[action];
    switch (action_enum) {
    case PhotoEditor::Actions::Rotate:
        Q_ASSERT(args.size() == 1);
        return rotation(args[0].toDouble());
        break;
    case PhotoEditor::Actions::Flip:
        Q_ASSERT(args.size() == 1);
        return flip(args[0]);
        break;
    case PhotoEditor::Actions::Scale:
        //implement later
        break;
    case PhotoEditor::Actions::Grayscale:
        Q_ASSERT(args.size() == 0);
        return grayscale();
        break;
    case PhotoEditor::Actions::Hue:
        Q_ASSERT(args.size() == 1);
        return hueShift(args[0].toInt());
    case PhotoEditor::Actions::ResetColor:
        Q_ASSERT(args.size() == 1);
        return resetColorChannel(args[0]);
    }
}

QList<QObject*> PhotoEditor::history() {
    int action_count = m_actions.index();
    QList<QObject*> history;
    for (int i = 0; i < action_count; i++) {
        QObject* data = dynamic_cast<const PhotoEditCommand*>(m_actions.command(i))->historyData();
        history.push_back(data);
    }
    return history;
}
void PhotoEditor::remove(int index) {
    int original_index = m_actions.index();
    m_actions.setIndex(index);
    QUndoCommand* to_delete = const_cast<QUndoCommand*>(m_actions.command(index));
    to_delete->setObsolete(true);
    m_actions.setIndex(original_index);
    update();
}
void PhotoEditor::swap(int index1, int index2) {
    if (index1 == index2) return;
    QList<PhotoEditCommand*> new_actions;
    for (int i = 0; i < m_actions.count(); ++i) {
        PhotoActionData* data = dynamic_cast<const PhotoEditCommand*>(m_actions.command(i))->historyData();
        new_actions.emplaceBack(createAction(data->action(), data->args()));
    }
    new_actions.swapItemsAt(index1, index2);
    m_current_image = m_original_image;
    m_actions.clear();
    for (PhotoEditCommand* cmd : new_actions) {
        cmd->setImage(&m_current_image);
        m_actions.push(cmd);
    }
    update();
}

void PhotoEditor::execute(PhotoEditCommand* action) {
    if (m_current_image.isNull() || m_preview_image.isNull()) {
        delete action;
        return;
    }
    if (m_current_action != nullptr) delete m_current_action;
    m_current_action = action;
    m_current_action->redo();

    emit(previewUpdated(m_preview_image));
    m_preview_image = m_current_image;

}
void PhotoEditor::approveChanges() {
    if (m_current_action == nullptr) return;
    m_current_action->setImage(&m_current_image);
    m_actions.push(m_current_action);
    m_current_action = 0;
    update();
}
void PhotoEditor::undo() {
    if (!m_actions.canUndo()) return;
    m_actions.undo();
    update();
}
void PhotoEditor::redo() {
    if (!m_actions.canRedo()) return;
    m_actions.redo();
    update();
}

PhotoEditCommand* PhotoEditor::rotation(qreal angle) {
    return new RotateImage(&m_preview_image, angle);
}
PhotoEditCommand* PhotoEditor::flip(QString orientation) {
    FlipImage::Orientation orientation_enum = orientation == "vertical" ? FlipImage::Orientation::Vertical : FlipImage::Orientation::Horizontal;
    return new FlipImage(&m_preview_image, orientation_enum);
}
PhotoEditCommand* PhotoEditor::scale(int width, int height) {
    return new ScaleImage(&m_preview_image, width, height);
}
PhotoEditCommand* PhotoEditor::grayscale() {
    return new ApplyGrayscale(&m_preview_image);
}
PhotoEditCommand* PhotoEditor::hueShift(int hue) {
    return new AdjustHue(&m_preview_image, hue);
}
PhotoEditCommand* PhotoEditor::resetColorChannel(QString channel) {
    QHash<QString, ResetColor::Color> translate{
        {"red", ResetColor::Color::Red},
        {"green", ResetColor::Color::Green},
        {"blue", ResetColor::Color::Blue}
    };
    return new ResetColor(&m_preview_image, translate[channel]);
}


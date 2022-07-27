#include "src/EditedImageProvider.h"

EditedImageProvider::EditedImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{}

EditedImageProvider::~EditedImageProvider()
{}

QPixmap EditedImageProvider::requestPixmap(const QString& id, QSize* size, const QSize& requested_size) {
    if (id == "preview") return m_preview_image;
    else if (id == "current") return m_current_image;
    else return QPixmap{};
}

void EditedImageProvider::updatePreview(const QImage& image) {
    m_preview_image = QPixmap::fromImage(image);
    emit previewUpdated();
}
void EditedImageProvider::updateCurrent(const QImage& image) {
    m_current_image = QPixmap::fromImage(image);
    emit currentUpdated();
}

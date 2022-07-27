#include "src/PhotoEditionCommands.h"
#include <QTransform>
#include <QVariant>

PhotoEditCommand::PhotoEditCommand(QImage* image, QUndoCommand* parent)
    : QUndoCommand(parent), m_image(image), m_history_data(0) {}
void PhotoEditCommand::setImage(QImage* image) {
    m_image = image;
}
void PhotoEditCommand::setHistoryData(PhotoActionData* data) {
    m_history_data = data;
}
PhotoActionData* PhotoEditCommand::historyData() const {
    return m_history_data;
}

RotateImage::RotateImage(QImage* image, qreal angle, QUndoCommand* parent)
    : PhotoEditCommand(image), m_angle(angle)
{
    setHistoryData(new PhotoActionData("Rotate by " + QString::number(m_angle),
        QString("rotate"),
        QStringList{ QString::number(m_angle) }
    ));
}
void RotateImage::redo() {
    *m_image = m_image->transformed(QTransform().rotate(m_angle));
}
void RotateImage::undo() {
    *m_image = m_image->transformed(QTransform().rotate(-m_angle));
}


FlipImage::FlipImage(QImage* image, FlipImage::Orientation orientation, QUndoCommand* parent)
    : PhotoEditCommand(image), m_orientation(orientation)
{
    setHistoryData(new PhotoActionData(
        (m_orientation == FlipImage::Orientation::Vertical ? "Vertical" : "Horizontal") + QString(" flip"),
        QString("flip"),
        QStringList{ QString(m_orientation == FlipImage::Orientation::Vertical ? "vertical" : "horizontal") }
    ));
}
void FlipImage::redo() {
    if (m_orientation == FlipImage::Orientation::Vertical)
        *m_image = m_image->mirrored(false, true);
    else //horizontal
        *m_image = m_image->mirrored(true, false);
}
void FlipImage::undo() {
    redo();
}

ScaleImage::ScaleImage(QImage* image, int width, int height, QUndoCommand* parent)
    : PhotoEditCommand(image, parent),
    m_goal_size(width, height), m_original_size(image->width(), image->height())
{
    setHistoryData(new PhotoActionData("Scaled to" + QString::number(width) + " x " + QString::number(height),
        QString("scale"),
        QStringList{ QString::number(width), QString::number(height) }
    ));
}
void ScaleImage::redo() {
    *m_image = m_image->scaled(m_goal_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}
void ScaleImage::undo() {
    *m_image = m_image->scaled(m_original_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

ApplyGrayscale::ApplyGrayscale(QImage* image, QUndoCommand* parent)
    : PhotoEditCommand(image, parent) {
    setHistoryData(new PhotoActionData(
        QString("Apply grayscale"),
        QString("grayscale"),
        QStringList{}
    ));
}
void ApplyGrayscale::redo() {
    m_preserved_image = *m_image;
    for (int y = 0; y < m_image->height(); ++y) {
        QRgb* line = reinterpret_cast<QRgb*>(m_image->scanLine(y));
        for (int x = 0; x < m_image->width(); ++x) {
            QRgb& pixel = line[x];
            int avg = (qRed(pixel) + qGreen(pixel) + qBlue(pixel))/3;
            pixel = qRgb(avg, avg, avg);
        }
    }
}
void ApplyGrayscale::undo() {
    *m_image = m_preserved_image;
}

AdjustHue::AdjustHue(QImage* image, int hue, QUndoCommand* parent)
    : PhotoEditCommand(image, parent), m_hue(hue) {
    setHistoryData(new PhotoActionData(
        "Adjust hue by " + QString::number(hue),
        QString("hue"),
        QStringList{ QString::number(hue) }
    ));
}
void AdjustHue::redo() {
    for (int y = 0; y < m_image->height(); ++y) {
        QRgb* line = reinterpret_cast<QRgb*>(m_image->scanLine(y));
        for (int x = 0; x < m_image->width(); ++x) {
            QColor color(line[x]);
            int new_hue = color.hue() + m_hue;
            if (new_hue < 0) new_hue += 360;
            color.setHsv(new_hue, color.saturation(), color.value());
            line[x] = color.rgb();
        }
    }
}
void AdjustHue::undo() {
    for (int y = 0; y < m_image->height(); ++y) {
        QRgb* line = reinterpret_cast<QRgb*>(m_image->scanLine(y));
        for (int x = 0; x < m_image->width(); ++x) {
            QColor color(line[x]);
            int new_hue = color.hue() - m_hue;
            if (new_hue < 0) new_hue += 360;
            color.setHsv(new_hue, color.saturation(), color.value());
            line[x] = color.rgb();
        }
    }
}

ResetColor::ResetColor(QImage* image, ResetColor::Color color, QUndoCommand* parent)
    : PhotoEditCommand(image), m_color(color) {
    setHistoryData(new PhotoActionData(
        (m_color == ResetColor::Color::Red ? "Red" : m_color == ResetColor::Color::Blue ? "Blue" : "Green") + QString(" channel reset"),
        QString("reset color"),
        QStringList{QString(m_color == ResetColor::Color::Red ? "red" : m_color == ResetColor::Color::Blue ? "blue" : "green") }
    ));
}
void ResetColor::redo() {
    m_preserved_image = *m_image;
    for (int y = 0; y < m_image->height(); ++y) {
        QRgb* line = reinterpret_cast<QRgb*>(m_image->scanLine(y));
        for (int x = 0; x < m_image->width(); ++x) {
            QRgb& pixel = line[x];
            int red = m_color == ResetColor::Color::Red ? 0 : qRed(pixel);
            int green = m_color == ResetColor::Color::Green ? 0 : qGreen(pixel);
            int blue = m_color == ResetColor::Color::Blue ? 0 : qBlue(pixel);
            pixel = qRgb(red, green, blue);
        }
    }
}
void ResetColor::undo() {
    *m_image = m_preserved_image;
}

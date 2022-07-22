#pragma once

#include <QQuickImageProvider>
#include <QImage>
#include <QPixmap>

class EditedImageProvider  : public QQuickImageProvider
{
    Q_OBJECT

public:
    EditedImageProvider();
    virtual ~EditedImageProvider() override;

    QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requested_size) override;
signals:
    void previewUpdated();
    void currentUpdated();
public slots:
    void updatePreview(const QImage& image);
    void updateCurrent(const QImage& image);
private:
    QPixmap m_preview_image;
    QPixmap m_current_image;
};

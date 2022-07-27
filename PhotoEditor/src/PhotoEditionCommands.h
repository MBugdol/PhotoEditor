#pragma once
#include <QUndoCommand>
#include <QImage>
#include "src/PhotoActionData.h"

class PhotoEditCommand : public QUndoCommand {
public:
    PhotoEditCommand(QImage* image, QUndoCommand* parent = 0);
    void setImage(QImage* image);
    void setHistoryData(PhotoActionData* data);
    PhotoActionData* historyData() const;
protected:
    QImage* m_image=0;
    PhotoActionData* m_history_data=0;
};

class RotateImage : public PhotoEditCommand
{

public:
    RotateImage(QImage* image, qreal angle, QUndoCommand* parent = 0);
    void redo() override;
    void undo() override;
private:
    qreal m_angle;
};

class FlipImage : public PhotoEditCommand {
public:
    enum class Orientation {
        Vertical,
        Horizontal
    };
    FlipImage(QImage* image, FlipImage::Orientation orientation, QUndoCommand* parent = 0);
    void redo() override;
    void undo() override;
private:
    FlipImage::Orientation m_orientation;
};

class ScaleImage : public PhotoEditCommand {
public:
    ScaleImage(QImage* image, int width, int height, QUndoCommand* parent = 0);
    void redo() override;
    void undo() override;
private:
    QImage m_preserved_image; //required?
    QSize m_original_size;
    QSize m_goal_size;
};

class ApplyGrayscale : public PhotoEditCommand {
public:
    ApplyGrayscale(QImage* image, QUndoCommand* parent = 0);
    void redo() override;
    void undo() override;
private:
    QImage m_preserved_image;
};

class AdjustHue : public PhotoEditCommand {
public:
    AdjustHue(QImage* image, int hue, QUndoCommand* parent = 0);
    void redo() override;
    void undo() override;
private:
    int m_hue;
};

class ResetColor : public PhotoEditCommand {
public:
    enum class Color {
        Red,
        Green,
        Blue
    };
    ResetColor(QImage* image, ResetColor::Color color, QUndoCommand* parent = 0);
    void redo();
    void undo();
private:
    ResetColor::Color m_color;
    QImage m_preserved_image;
};

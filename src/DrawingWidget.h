#pragma once

#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include <QStack>
#include <QTabletEvent>

class DrawingWidget : public QWidget
{
    Q_OBJECT

public:
    DrawingWidget(QWidget *parent = nullptr);
    bool loadImage(const QString &fileName);
    void setPenColor(const QColor &color);
    void setPenWidth(int width);
    QColor penColor() const { return m_penColor; };
    void undo();
    void redo();
    void clear();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void tabletEvent(QTabletEvent *event) override;

private:
    QImage m_originalImage;
    QImage m_displayImage;
    QStack<QImage> m_undoStack;
    QStack<QImage> m_redoStack;
    QPoint m_lastPoint;
    bool m_drawing;
    QColor m_penColor;
    int m_penWidth;

    void saveState();
    void drawLineTo(const QPoint &endPoint);
};
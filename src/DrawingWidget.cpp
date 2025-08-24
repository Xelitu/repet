#include "DrawingWidget.h"
#include <QFileDialog>
#include <QPainter>

DrawingWidget::DrawingWidget(QWidget *parent)
    : QWidget(parent), m_drawing(false), m_penColor(Qt::red), m_penWidth(3)
{
    setAttribute(Qt::WA_StaticContents);
}

bool DrawingWidget::loadImage(const QString &fileName)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;

    m_originalImage = loadedImage.convertToFormat(QImage::Format_ARGB32);
    m_displayImage = m_originalImage.copy();
    
    m_undoStack.clear();
    m_redoStack.clear();
    
    update();
    return true;
}

void DrawingWidget::setPenColor(const QColor &color)
{
    m_penColor = color;
}

void DrawingWidget::setPenWidth(int width)
{
    m_penWidth = width;
}

void DrawingWidget::undo()
{
    if (m_undoStack.isEmpty())
        return;

    m_redoStack.push(m_displayImage);
    m_displayImage = m_undoStack.pop();
    update();
}

void DrawingWidget::redo()
{
    if (m_redoStack.isEmpty())
        return;

    m_undoStack.push(m_displayImage);
    m_displayImage = m_redoStack.pop();
    update();
}

void DrawingWidget::clear()
{
    m_displayImage = m_originalImage.copy();
    m_undoStack.clear();
    m_redoStack.clear();
    update();
}

void DrawingWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, m_displayImage, dirtyRect);
}

void DrawingWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && !m_originalImage.isNull()) {
        saveState();
        m_lastPoint = event->pos();
        m_drawing = true;
    }
}

void DrawingWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && m_drawing) {
        drawLineTo(event->pos());
    }
}

void DrawingWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_drawing) {
        drawLineTo(event->pos());
        m_drawing = false;
    }
}

void DrawingWidget::tabletEvent(QTabletEvent *event)
{
    if (event->type() == QEvent::TabletPress && !m_originalImage.isNull()) {
        saveState();
        m_lastPoint = event->pos();
        m_drawing = true;
        event->accept();
    } else if (event->type() == QEvent::TabletMove && m_drawing) {
        drawLineTo(event->pos());
        event->accept();
    } else if (event->type() == QEvent::TabletRelease && m_drawing) {
        drawLineTo(event->pos());
        m_drawing = false;
        event->accept();
    } else {
        event->ignore();
    }
}

void DrawingWidget::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&m_displayImage);
    painter.setRenderHint(QPainter::Antialiasing);
    
    painter.setPen(QPen(m_penColor, m_penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(m_lastPoint, endPoint);
    
    int rad = (m_penWidth / 2) + 2;
    update(QRect(m_lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    
    m_lastPoint = endPoint;
}

void DrawingWidget::saveState()
{
    m_undoStack.push(m_displayImage.copy());
    m_redoStack.clear();
}
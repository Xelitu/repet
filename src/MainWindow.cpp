#include "MainWindow.h"
#include <QFileDialog>

MainWindow::MainWindow()
{
    m_drawingWidget = new DrawingWidget;
    setCentralWidget(m_drawingWidget);

    createActions();
    createToolBar();

    setWindowTitle(tr("Рисование по изображению"));
    resize(800, 600);
}

void MainWindow::createActions()
{
    m_openAct = new QAction(tr("&Открыть"), this);
    connect(m_openAct, &QAction::triggered, this, &MainWindow::open);

    m_saveAct = new QAction(tr("&Сохранить"), this);
    connect(m_saveAct, &QAction::triggered, this, &MainWindow::save);

    m_penColorAct = new QAction(tr("&Цвет"), this);
    connect(m_penColorAct, &QAction::triggered, this, &MainWindow::penColor);

    m_clearAct = new QAction(tr("&Очистить"), this);
    connect(m_clearAct, &QAction::triggered, m_drawingWidget, &DrawingWidget::clear);

    m_undoAct = new QAction(tr("&Отменить"), this);
    m_undoAct->setShortcut(QKeySequence::Undo);
    connect(m_undoAct, &QAction::triggered, m_drawingWidget, &DrawingWidget::undo);

    m_redoAct = new QAction(tr("&Повторить"), this);
    m_redoAct->setShortcut(QKeySequence::Redo);
    connect(m_redoAct, &QAction::triggered, m_drawingWidget, &DrawingWidget::redo);
}

void MainWindow::createToolBar()
{
    QToolBar *toolBar = addToolBar(tr("Инструменты"));
    
    toolBar->addAction(m_openAct);
    toolBar->addAction(m_saveAct);
    toolBar->addAction(m_penColorAct);
    toolBar->addAction(m_clearAct);
    toolBar->addAction(m_undoAct);
    toolBar->addAction(m_redoAct);

    QSpinBox *widthSpinBox = new QSpinBox;
    widthSpinBox->setRange(1, 20);
    widthSpinBox->setValue(3);
    connect(widthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::penWidth);
    
    toolBar->addWidget(new QLabel(tr("Толщина:")));
    toolBar->addWidget(widthSpinBox);
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Открыть изображение"), "", tr("Images (*.png *.jpg *.bmp)"));
    if (!fileName.isEmpty())
        m_drawingWidget->loadImage(fileName);
}

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Сохранить изображение"), "", tr("Images (*.png *.jpg *.bmp)"));
    if (!fileName.isEmpty())
        m_drawingWidget->grab().save(fileName);
}

void MainWindow::penColor()
{
    QColor newColor = QColorDialog::getColor(m_drawingWidget->penColor());
    if (newColor.isValid())
        m_drawingWidget->setPenColor(newColor);
}

void MainWindow::penWidth(int width)
{
    m_drawingWidget->setPenWidth(width);
}
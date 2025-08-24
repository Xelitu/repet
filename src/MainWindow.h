#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QColorDialog>
#include <QSpinBox>
#include <QLabel>

#include "DrawingWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void open();
    void save();
    void penColor();
    void penWidth(int width);

private:
    void createActions();
    void createToolBar();

    DrawingWidget *m_drawingWidget;
    QAction *m_openAct;
    QAction *m_saveAct;
    QAction *m_penColorAct;
    QAction *m_clearAct;
    QAction *m_undoAct;
    QAction *m_redoAct;
};
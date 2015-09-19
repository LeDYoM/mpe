#include "mainwindow.h"
#include "mpeglwidget.h"
#include <QOpenGLContext>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    widget = new MPEGLWidget(this);
    this->setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    widget->context()->deleteLater();
    widget->deleteLater();
}

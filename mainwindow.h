#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MPEGLWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    inline MPEGLWidget *getWidget() const { return widget; }

private:
    MPEGLWidget *widget;
};

#endif // MAINWINDOW_H

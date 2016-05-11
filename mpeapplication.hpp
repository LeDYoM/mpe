#ifndef MPEAPPLICATION_H
#define MPEAPPLICATION_H

#include <QApplication>
#include "mainwindow.hpp"

class MPEApplication : public QApplication
{
public:
    using QApplication::QApplication;
    virtual ~MPEApplication();

    void start();
    void finish();

    inline MPEGLWidget *getWidget() const { return mainWindow->getWidget(); }

private:
    MainWindow *mainWindow;
};

#define mpeApp (static_cast<MPEApplication *>(QCoreApplication::instance()))

#endif // MPEAPPLICATION_H

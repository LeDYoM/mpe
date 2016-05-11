#include "mpeapplication.hpp"
#include "mainwindow.hpp"

MPEApplication::~MPEApplication()
{

}

void MPEApplication::start()
{
    mainWindow = new MainWindow();
    mainWindow->show();
}

void MPEApplication::finish()
{
    mainWindow->deleteLater();
    mainWindow = nullptr;
}


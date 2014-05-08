#include "mainWindow.h"
#include "ui_mainWindow.h"

#include <QTranslator>
#include <QSplitter>


mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);
}


mainWindow::~mainWindow()
{
    delete ui;
}


void mainWindow::newDSM()
{
}


void mainWindow::openDSM()
{
}


void mainWindow::saveDSM()
{
}


void mainWindow::saveAsDSM()
{
}


void mainWindow::newClustering()
{
}


void mainWindow::openClustering()
{
}


void mainWindow::saveClustering()
{
}


void mainWindow::saveAsClustering()
{
}


void mainWindow::exitProgram()
{
}


void mainWindow::redraw()
{
}


void mainWindow::showRowLabels()
{
}


void mainWindow::about()
{
}


void mainWindow::expandAll()
{
}


void mainWindow::collapseAll()
{
}


void mainWindow::group()
{
}


void mainWindow::ungroup()
{
}


void mainWindow::moveUp()
{
}


void mainWindow::moveDown()
{
}


void mainWindow::addEntity()
{
}


void mainWindow::deleteEntity()
{
}

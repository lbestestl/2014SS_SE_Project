#include "mainWindow.h"
#include "ui_mainWindow.h"
#include "dsmModel.h"
#include "clusterModel.h"

#include <QTranslator>
#include <QSplitter>
#include <QMessageBox>
#include <QFileDialog>
#include <QList>
#include <QDebug>


//this variables will be replaced by globalInst class
DsmModel* dsm;
ClusterModel* clm;
QModelIndex* temptest;


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
    dsm = new DsmModel(1);
    ui->tableView->setModel(dsm);
}


void mainWindow::openDSM()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open DSM"), "" , tr("DSM files (*.dsm);;All files (*.*)"));
    QFile fin(fileName);
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text))
         return;

    QString a = fin.readLine();
    int num = a.toInt();
    fin.close();

    dsm = new DsmModel(num);
    dsm->load(fileName);
    ui->tableView->setModel(dsm);
}


void mainWindow::saveDSM()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save DSM"), tr("out.dsm"), tr("DSM files (*.dsm)"));
    QFile fout(fileName);
    if (!fout.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    dsm->store(fileName);
}


void mainWindow::saveAsDSM()
{
}


void mainWindow::newClustering()
{
}


void mainWindow::openClustering()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Clustering"), "" , tr("Cluster files (*.clsx);;All files (*.*)"));
    clm = new ClusterModel();
    clm->load(fileName);
    ui->treeView->setModel(clm);
}


void mainWindow::saveClustering()
{
/*
    QModelIndex* in = new QModelIndex(0, 0, clm->invisibleRootItem(), (*clm));
    temptest = new QModelIndex(clm->index(0, 0, clm->indexFromItem(cur)));
    QModelIndex in2 = clm->index(0, 0, clm->indexFromItem(cur));
    qDebug()<<in2;
*/
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Clustering"), tr("out.clsx"), tr("Cluster files (*.clsx)"));
    clm->store(fileName);
}


void mainWindow::saveAsClustering()
{
}


void mainWindow::redraw()
{
    if (ui->treeView->isExpanded(*temptest))
        qDebug()<<"Yes";
    else
        qDebug()<<"No";
}


void mainWindow::showRowLabels()
{
}


void mainWindow::about()
{
    QMessageBox::about(this, tr("About Design structure matrix tool"),
                       QString("<b>DSMTT</b> version: %1 <br> "
                               "<br>Copyright (c) 2014 %2<br>"
                               "<br> Authors:"
                               "<li><a href=\"mailto:%3\">%4</a><li>").
                       arg(tr("1405.1")).
                       arg(tr("CAU CSE Team")).
                       arg(tr("lbestestl@gmail.com")).
                       arg(tr("Yi, Ho-jun (20101575)")));
}


void mainWindow::expandAll()
{
    ui->treeView->expandAll();
}


void mainWindow::collapseAll()
{
    ui->treeView->collapseAll();
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


void mainWindow::closeEvent(QCloseEvent* event)
{
    /*
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Save Changes?"), tr("cluster file is changed."), QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes);
    if (reply == QMessageBox::Cancel) {
        event->ignore();
    } else if (reply == QMessageBox::No) {
        event->accept();
    } else if (reply == QMessageBox::Yes) {
        event->accept();
    }
*/
    event->accept();
}

#include "mainWindow.h"
#include "ui_mainWindow.h"
#include "dsmModel.h"
#include "clusterModel.h"
#include "globalInst.h"

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
    GlobalInst::getInstance()->oriDsm = new DsmModel(0);
    GlobalInst::getInstance()->curDsm = new DsmModel(0);
    GlobalInst::getInstance()->dsmExist = true;
    addEntity();
    ui->tableView->setModel(GlobalInst::getInstance()->curDsm);
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
    if (GlobalInst::getInstance()->oriDsm != NULL) {
        GlobalInst::getInstance()->oriDsm->deleteAll();
        GlobalInst::getInstance()->oriDsm = NULL;
    }
    if (GlobalInst::getInstance()->curDsm != NULL) {
        GlobalInst::getInstance()->curDsm->deleteAll();
        GlobalInst::getInstance()->curDsm = NULL;
    }

    GlobalInst::getInstance()->oriDsm = new DsmModel(num);
    GlobalInst::getInstance()->oriDsm->load(fileName);
    GlobalInst::getInstance()->curDsm = new DsmModel(num);
    GlobalInst::getInstance()->curDsm->load(fileName);
    GlobalInst::getInstance()->dsmExist = true;
    ui->tableView->setModel(GlobalInst::getInstance()->curDsm);

}


void mainWindow::saveDSM()
{
    if (GlobalInst::getInstance()->dsmPath == "") {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save DSM"), tr("out.dsm"), tr("DSM files (*.dsm)"));
        GlobalInst::getInstance()->dsmPath = fileName;
    }
    GlobalInst::getInstance()->oriDsm->store(GlobalInst::getInstance()->dsmPath);
}


void mainWindow::saveAsDSM()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as DSM"), tr("out.dsm"), tr("DSM files (*.dsm)"));
    GlobalInst::getInstance()->dsmPath = fileName;
    GlobalInst::getInstance()->oriDsm->store(GlobalInst::getInstance()->dsmPath);
}


void mainWindow::newClustering()
{
}


void mainWindow::openClustering()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Clustering"), "" , tr("Cluster files (*.clsx);;All files (*.*)"));
    GlobalInst::getInstance()->clm = new ClusterModel();
    GlobalInst::getInstance()->clm->load(fileName);
    ui->treeView->setModel(GlobalInst::getInstance()->clm);
}


void mainWindow::saveClustering()
{
/*
    QModelIndex* in = new QModelIndex(0, 0, clm->invisibleRootItem(), (*clm));
    temptest = new QModelIndex(clm->index(0, 0, clm->indexFromItem(cur)));
    QModelIndex in2 = clm->index(0, 0, clm->indexFromItem(cur));
    qDebug()<<in2;
*/
    if (GlobalInst::getInstance()->clmPath == "") {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save Clustering"), tr("out.clsx"), tr("Cluster files (*.clsx)"));
        GlobalInst::getInstance()->dsmPath = fileName;
    }
    GlobalInst::getInstance()->clm->store(GlobalInst::getInstance()->dsmPath);
}


void mainWindow::saveAsClustering()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as Clustering"), tr("out.clsx"), tr("Cluster files (*.clsx)"));
    GlobalInst::getInstance()->clm->store(GlobalInst::getInstance()->dsmPath);
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
    if (!GlobalInst::getInstance()->dsmExist)
        return;
    GlobalInst::getInstance()->clmModified = true;
}


void mainWindow::ungroup()
{
    if (!GlobalInst::getInstance()->dsmExist)
        return;
    GlobalInst::getInstance()->clmModified = true;
}


void mainWindow::moveUp()
{
    if (!GlobalInst::getInstance()->dsmExist)
        return;
    GlobalInst::getInstance()->clmModified = true;
}


void mainWindow::moveDown()
{
    if (!GlobalInst::getInstance()->dsmExist)
        return;
    GlobalInst::getInstance()->clmModified = true;
}


void mainWindow::addEntity()
{
    if (!GlobalInst::getInstance()->dsmExist)
        return;
    GlobalInst::getInstance()->dsmModified = true;
    QList<QStandardItem*> orow;
    for (int i = 0; i < GlobalInst::getInstance()->oriDsm->rowCount(); i++) {
        QStandardItem* oi = new QStandardItem("0");
        orow.append(oi);
    }
    GlobalInst::getInstance()->oriDsm->insertRow(0, orow);
    QList<QStandardItem*> ocol;
    for (int i = 0 ; i < GlobalInst::getInstance()->oriDsm->rowCount(); i++) {
        QStandardItem* oi = new QStandardItem("0");
        ocol.append(oi);
    }
    GlobalInst::getInstance()->oriDsm->insertColumn(0, ocol);

    QList<QStandardItem*> crow;
    for (int i = 0; i < GlobalInst::getInstance()->curDsm->rowCount(); i++) {
        QStandardItem* ci = new QStandardItem("0");
        crow.append(ci);
    }
    GlobalInst::getInstance()->curDsm->insertRow(0, crow);
    QList<QStandardItem*> ccol;
    for (int i = 0 ; i < GlobalInst::getInstance()->curDsm->rowCount(); i++) {
        QStandardItem* ci = new QStandardItem("0");
        ccol.append(ci);
    }
    GlobalInst::getInstance()->curDsm->insertColumn(0, ccol);
}


void mainWindow::deleteEntity()
{
    if (!GlobalInst::getInstance()->dsmExist)
        return;
    GlobalInst::getInstance()->dsmModified = true;
}


void mainWindow::closeEvent(QCloseEvent* event)
{
    if (GlobalInst::getInstance()->clmModified == true) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Save Changes?"), tr("cluster file is changed."), QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes);
        if (reply == QMessageBox::Cancel) {
            event->ignore();
            return;
        } else if (reply == QMessageBox::Yes) {
            saveClustering();
        } else {
            ;
        }
    }
    if (GlobalInst::getInstance()->dsmModified == true) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Save Changes?"), tr("dsm file is changed."), QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes);
        if (reply == QMessageBox::Cancel) {
            event->ignore();
            return;
        } else if (reply == QMessageBox::Yes) {
            saveDSM();
        } else {
            ;
        }
    }
    event->accept();
}


void mainWindow::sort()
{
    ui->treeView->sortByColumn(0, Qt::AscendingOrder);
    ui->treeView->setSortingEnabled(true);
}


void mainWindow::rename()
{
}


void mainWindow::partition()
{
}

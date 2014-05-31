#include "mainWindow.h"
#include "ui_mainWindow.h"
#include "globalInst.h"

#include <QTranslator>
#include <QMessageBox>
#include <QFileDialog>
#include <QList>
#include <QDebug>


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
    if (!confirmSaveDsm())
        return;
    clearDsm();

    GlobalInst::getInstance()->oriDsm = new DsmModel(0);
    GlobalInst::getInstance()->curDsm = new DsmModel(0);

    ui->tableView->setModel(GlobalInst::getInstance()->curDsm);
    GlobalInst::getInstance()->dsmExist = true;
    GlobalInst::getInstance()->dsmModified = true;
    newClustering();
    addEntity();
}


void mainWindow::openDSM()
{
    if (!confirmSaveDsm())
        return;
    clearDsm();

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open DSM"), "" , tr("DSM files (*.dsm);;All files (*.*)"));
    QFile fin(fileName);
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text))
         return;

    QString a = fin.readLine();
    int num = a.toInt();
    fin.close();

    GlobalInst::getInstance()->oriDsm = new DsmModel(num);
    GlobalInst::getInstance()->oriDsm->load(fileName);
    GlobalInst::getInstance()->curDsm = new DsmModel(num);
    GlobalInst::getInstance()->curDsm->load(fileName);

    ui->tableView->setModel(GlobalInst::getInstance()->curDsm);
    GlobalInst::getInstance()->dsmExist = true;

    newClustering();
}


void mainWindow::saveDSM()
{
    if (GlobalInst::getInstance()->dsmPath == "") {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save DSM"), tr("out.dsm"), tr("DSM files (*.dsm)"));
        if (fileName == "")
            return;
        GlobalInst::getInstance()->dsmPath = fileName;
    }
    GlobalInst::getInstance()->oriDsm->store(GlobalInst::getInstance()->dsmPath);
    GlobalInst::getInstance()->dsmModified = false;
}


void mainWindow::saveAsDSM()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as DSM"), tr("out.dsm"), tr("DSM files (*.dsm)"));
    if (fileName == "")
        return;
    GlobalInst::getInstance()->dsmPath = fileName;

    GlobalInst::getInstance()->oriDsm->store(GlobalInst::getInstance()->dsmPath);
    GlobalInst::getInstance()->dsmModified = false;
}


void mainWindow::newClustering()
{
    if (!GlobalInst::getInstance()->dsmExist)
        return;

    if (!confirmSaveClm())
        return;
    clearClm();

    GlobalInst::getInstance()->clm = new ClusterModel();
    GlobalInst::getInstance()->clm->load(GlobalInst::getInstance()->oriDsm);

    ui->treeView->setModel(GlobalInst::getInstance()->clm);
    GlobalInst::getInstance()->clmModified = true;
}


void mainWindow::openClustering()
{
    if (!GlobalInst::getInstance()->dsmExist)
        return;

    if (!confirmSaveClm())
        return;
    clearClm();

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Clustering"), "" , tr("Cluster files (*.clsx);;All files (*.*)"));
    if (fileName == "")
        return;

    GlobalInst::getInstance()->clm = new ClusterModel();
    GlobalInst::getInstance()->clm->load(fileName);

    ui->treeView->setModel(GlobalInst::getInstance()->clm);
}


void mainWindow::saveClustering()
{
    if (GlobalInst::getInstance()->clmPath == "") {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save Clustering"), tr("out.clsx"), tr("Cluster files (*.clsx)"));
        if (fileName == "")
            return;
        GlobalInst::getInstance()->dsmPath = fileName;
    }
    GlobalInst::getInstance()->clm->store(GlobalInst::getInstance()->dsmPath);
    GlobalInst::getInstance()->clmModified = false;
}


void mainWindow::saveAsClustering()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as Clustering"), tr("out.clsx"), tr("Cluster files (*.clsx)"));
    if (fileName == "")
        return;
    GlobalInst::getInstance()->clm->store(GlobalInst::getInstance()->dsmPath);
    GlobalInst::getInstance()->clmModified = false;
}


void mainWindow::redraw()
{
}


void mainWindow::showRowLabels(bool check)
{

}


void mainWindow::about()
{
    QMessageBox::about(this, tr("About Design structure matrix tool"),
                       QString("<b>DSMTT</b> version: %1 <br> "
                               "<br>Copyright (c) 2014 %2<br>"
                               "<br> Authors:"
                               "<li><a href=\"mailto:%3\">%4</a><li>").
                       arg(tr("1406.1")).
                       arg(tr("CAU CSE Team")).
                       arg("lbestestl@gmail.com").
                       arg("Yi, Ho-jun (20101575)"));
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
    if (ui->treeView->selectionModel()->selectedIndexes().isEmpty())
        return;

    GlobalInst::getInstance()->clm->group(ui->treeView->selectionModel());
    GlobalInst::getInstance()->clmModified = true;
}


void mainWindow::ungroup()
{
    if (!GlobalInst::getInstance()->dsmExist)
        return;
    if (ui->treeView->selectionModel()->selectedIndexes().isEmpty())
        return;

    GlobalInst::getInstance()->clm->ungroup(ui->treeView->selectionModel());
    GlobalInst::getInstance()->clmModified = true;
}


void mainWindow::moveUp()
{
    if (!GlobalInst::getInstance()->dsmExist)
        return;

    GlobalInst::getInstance()->clm->moveUp(ui->treeView->selectionModel());
    GlobalInst::getInstance()->clmModified = true;
}


void mainWindow::moveDown()
{
    if (!GlobalInst::getInstance()->dsmExist)
        return;

    GlobalInst::getInstance()->clm->moveDown(ui->treeView->selectionModel());
    GlobalInst::getInstance()->clmModified = true;
}


void mainWindow::addEntity()
{
    if (!GlobalInst::getInstance()->dsmExist)
        return;

    GlobalInst::getInstance()->oriDsm->appendEntity();
    GlobalInst::getInstance()->curDsm->appendEntity();
    GlobalInst::getInstance()->clm->appendEntity(GlobalInst::getInstance()->oriDsm->rowCount());
    GlobalInst::getInstance()->dsmModified = true;
    GlobalInst::getInstance()->clmModified = true;
}


void mainWindow::deleteEntity()
{
    if (!GlobalInst::getInstance()->dsmExist)
        return;
    GlobalInst::getInstance()->dsmModified = true;
    ui->treeView->selectionModel()->parent();

    GlobalInst::getInstance()->dsmModified = true;
    GlobalInst::getInstance()->clmModified = true;
}


void mainWindow::closeEvent(QCloseEvent* event)
{
    event->ignore();
    if (confirmSaveClm() && confirmSaveDsm())
        event->accept();
}


void mainWindow::sort()
{
    if (!GlobalInst::getInstance()->dsmExist)
        return;

    ui->treeView->sortByColumn(0, Qt::AscendingOrder);
    GlobalInst::getInstance()->clmModified = true;
}


void mainWindow::partition()
{
    GlobalInst::getInstance()->clmModified = true;
}


bool mainWindow::confirmSaveDsm()
{
    if (GlobalInst::getInstance()->dsmModified == true) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Save Changes?"), tr("dsm file is changed."), QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes);
        if (reply == QMessageBox::Cancel) {
            return false;
        } else if (reply == QMessageBox::Yes) {
            saveDSM();
        } else {
            ;
        }
    }
    return true;
}

bool mainWindow::confirmSaveClm()
{
    if (GlobalInst::getInstance()->clmModified == true) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Save Changes?"), tr("cluster file is changed."), QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes);
        if (reply == QMessageBox::Cancel) {
            return false;
        } else if (reply == QMessageBox::Yes) {
            saveClustering();
        } else {
            ;
        }
    }
    return true;
}


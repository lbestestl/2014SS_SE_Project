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
    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(treeViewClicked(QModelIndex)));
}


mainWindow::~mainWindow()
{
    delete ui;
}


void mainWindow::newDSM()
{
    if (GlobalInst::getInstance()->dsmModified == true) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Save Changes?"), tr("dsm file is changed."), QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes);
        if (reply == QMessageBox::Cancel) {
            return;
        } else if (reply == QMessageBox::Yes) {
            saveDSM();
        } else {
            ;
        }
    }
    clearDsm();
    GlobalInst::getInstance()->oriDsm = new DsmModel(0);
    GlobalInst::getInstance()->curDsm = new DsmModel(0);
    GlobalInst::getInstance()->dsmExist = true;
    addEntity();
    ui->tableView->setModel(GlobalInst::getInstance()->curDsm);
    newClustering();
}


void mainWindow::openDSM()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open DSM"), "" , tr("DSM files (*.dsm);;All files (*.*)"));
    QFile fin(fileName);
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text))
         return;

    if (GlobalInst::getInstance()->dsmModified == true) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Save Changes?"), tr("dsm file is changed."), QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes);
        if (reply == QMessageBox::Cancel) {
            return;
        } else if (reply == QMessageBox::Yes) {
            saveDSM();
        } else {
            ;
        }
    }
    clearDsm();
    QString a = fin.readLine();
    int num = a.toInt();
    fin.close();

    GlobalInst::getInstance()->oriDsm = new DsmModel(num);
    GlobalInst::getInstance()->oriDsm->load(fileName);
    GlobalInst::getInstance()->curDsm = new DsmModel(num);
    GlobalInst::getInstance()->curDsm->load(fileName);
    GlobalInst::getInstance()->dsmExist = true;
    ui->tableView->setModel(GlobalInst::getInstance()->curDsm);
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
}


void mainWindow::saveAsDSM()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as DSM"), tr("out.dsm"), tr("DSM files (*.dsm)"));
    if (fileName == "")
        return;
    GlobalInst::getInstance()->dsmPath = fileName;
    GlobalInst::getInstance()->oriDsm->store(GlobalInst::getInstance()->dsmPath);
}


void mainWindow::newClustering()
{
    if (GlobalInst::getInstance()->clmModified == true) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Save Changes?"), tr("cluster file is changed."), QMessageBox::No | QMessageBox::Yes);
        if (reply == QMessageBox::Yes) {
            saveClustering();
        } else {
            ;
        }
    }
    clearClm();
    if (!GlobalInst::getInstance()->dsmExist)
        return;
    GlobalInst::getInstance()->clm = new ClusterModel();
    QStandardItem* cur = GlobalInst::getInstance()->clm->invisibleRootItem();
    QStandardItem* item = new QStandardItem("$root");
    cur->appendRow(item);
    cur = item;
    for (int i = 0; i < GlobalInst::getInstance()->oriDsm->rowCount(); i++) {
        item = new QStandardItem(GlobalInst::getInstance()->oriDsm->verticalHeaderItem(i)->text());
        item->setEditable(false);
        cur->appendRow(item);
    }
    ui->treeView->setModel(GlobalInst::getInstance()->clm);
    GlobalInst::getInstance()->clmModified = true;
}


void mainWindow::openClustering()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Clustering"), "" , tr("Cluster files (*.clsx);;All files (*.*)"));
    if (fileName == "")
        return;
    if (GlobalInst::getInstance()->clmModified == true) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Save Changes?"), tr("cluster file is changed."), QMessageBox::No | QMessageBox::Yes);
        if (reply == QMessageBox::Yes) {
            saveClustering();
        } else {
            ;
        }
    }
    clearClm();
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
}


void mainWindow::saveAsClustering()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as Clustering"), tr("out.clsx"), tr("Cluster files (*.clsx)"));
    if (fileName == "")
        return;
    GlobalInst::getInstance()->clm->store(GlobalInst::getInstance()->dsmPath);
}


void mainWindow::redraw()
{
//    if (ui->treeView->isExpanded(*temptest))
//        qDebug()<<"Yes";
//    else
//        qDebug()<<"No";
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
                       arg(tr("1405.1")).
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
    else
        GlobalInst::getInstance()->clmModified = true;

    QStandardItem* cur = GlobalInst::getInstance()->clm->itemFromIndex(ui->treeView->selectionModel()->selectedIndexes().first());
    QStandardItem* par = static_cast<QStandardItem*>(cur->parent());
    if (par == NULL)
        return;
    cur = new QStandardItem("group");
    cur->setEditable(true);
    par->insertRow(ui->treeView->selectionModel()->selectedIndexes().first().row(),cur);

    int count = ui->treeView->selectionModel()->selectedIndexes().count();
    for (int i = 0; i < count ; i++) {
        QList<QStandardItem*> item = par->takeRow(GlobalInst::getInstance()->clm->itemFromIndex(ui->treeView->selectionModel()->selectedIndexes().first())->row());
        cur->appendRow(item);
    }
}


void mainWindow::ungroup()
{
    if (!GlobalInst::getInstance()->dsmExist)
            return;
    GlobalInst::getInstance()->clmModified = true;
    if (ui->treeView->selectionModel()->selectedIndexes().isEmpty())
        return;

    int count = ui->treeView->selectionModel()->selectedIndexes().count();
    for (int i = 0; i < count; i++) {
        QStandardItem* cur = GlobalInst::getInstance()->clm->itemFromIndex(ui->treeView->selectionModel()->selectedIndexes().takeFirst());
        if (!cur->hasChildren())
            continue;
        QStandardItem* par = static_cast<QStandardItem*>(cur->parent());
        if (par == NULL)
            continue;
        QStandardItem* gpar = static_cast<QStandardItem*>(cur->parent());
        if (gpar == NULL)
            continue;
        int count = cur->rowCount();
        for (int i = 0; i < count; i++) {
            QList<QStandardItem*> item = cur->takeRow(0);
            par->insertRow(cur->row(), item);
        }
        par->takeRow(cur->row());
    }
}


void mainWindow::moveUp()
{
    if (!GlobalInst::getInstance()->dsmExist)
        return;
    GlobalInst::getInstance()->clmModified = true;
    int count = ui->treeView->selectionModel()->selectedIndexes().count();
    for (int i = 0; i < count; i++) {
        QStandardItem* cur = GlobalInst::getInstance()->clm->itemFromIndex(ui->treeView->selectionModel()->selectedIndexes().at(0));
        int r = cur->row();
        QStandardItem* par = static_cast<QStandardItem*>(cur->parent());
        if (par == NULL)
            continue;
        if (r - 1 <= -1)
            continue;
        QList<QStandardItem*> item = par->takeRow(r);
        par->insertRow(r-1, item);
    }
}


void mainWindow::moveDown()
{
    if (!GlobalInst::getInstance()->dsmExist)
        return;
    GlobalInst::getInstance()->clmModified = true;
    int count = ui->treeView->selectionModel()->selectedIndexes().count();
    for (int i = 0; i < count; i++) {
        QStandardItem* cur = GlobalInst::getInstance()->clm->itemFromIndex(ui->treeView->selectionModel()->selectedIndexes().at(count-1-i));
        int r = cur->row();
        QStandardItem* par = static_cast<QStandardItem*>(cur->parent());
        if (par == NULL)
            continue;
        if (r + 1 >= par->rowCount())
            continue;
        QList<QStandardItem*> item = par->takeRow(r);
        par->insertRow(r+1, item);
    }
}


void mainWindow::addEntity()
{
    if (!GlobalInst::getInstance()->dsmExist)
        return;
    GlobalInst::getInstance()->dsmModified = true;
    QList<QStandardItem*> orow;
    int n = GlobalInst::getInstance()->oriDsm->rowCount();
    for (int i = 0; i < GlobalInst::getInstance()->oriDsm->rowCount(); i++) {
        QStandardItem* oi = new QStandardItem("0");
        orow.append(oi);
    }
    GlobalInst::getInstance()->oriDsm->insertRow(n, orow);
    QList<QStandardItem*> ocol;
    for (int i = 0 ; i < GlobalInst::getInstance()->oriDsm->rowCount(); i++) {
        QStandardItem* oi = new QStandardItem("0");
        ocol.append(oi);
    }
    GlobalInst::getInstance()->oriDsm->insertColumn(n, ocol);
    QStandardItem *ohi = new QStandardItem(QString::number(n+1));
    GlobalInst::getInstance()->oriDsm->setVerticalHeaderItem(n, ohi);

    QList<QStandardItem*> crow;
    n = GlobalInst::getInstance()->curDsm->rowCount();
    for (int i = 0; i < GlobalInst::getInstance()->curDsm->rowCount(); i++) {
        QStandardItem* ci = new QStandardItem("0");
        crow.append(ci);
    }
    GlobalInst::getInstance()->curDsm->insertRow(n, crow);
    QList<QStandardItem*> ccol;
    for (int i = 0 ; i < GlobalInst::getInstance()->curDsm->rowCount(); i++) {
        QStandardItem* ci = new QStandardItem("0");
        ccol.append(ci);
    }
    GlobalInst::getInstance()->curDsm->insertColumn(n, ccol);
    QStandardItem *chi = new QStandardItem(QString::number(n+1));
    GlobalInst::getInstance()->curDsm->setVerticalHeaderItem(n, chi);

    QStandardItem* ci = new QStandardItem(QString::number(n+1));
    ci->setEditable(false);
    GlobalInst::getInstance()->clm->invisibleRootItem()->child(0)->appendRow(ci);
}


void mainWindow::deleteEntity()
{
    if (!GlobalInst::getInstance()->dsmExist)
        return;
    GlobalInst::getInstance()->dsmModified = true;
    ui->treeView->selectionModel()->parent();
}


void mainWindow::closeEvent(QCloseEvent* event)
{
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

}


void mainWindow::treeViewClicked(QModelIndex mi)
{
//    qDebug()<<mi.data()<<mi.row()<<mi.column()<<mi.internalId();
}

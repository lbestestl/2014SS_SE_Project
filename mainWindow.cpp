#include "mainWindow.h"
#include "ui_mainWindow.h"
#include "dsmModel.h"

#include <QTranslator>
#include <QSplitter>
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
    DsmModel* dsm = new DsmModel(1);
    ui->tableView->setModel(dsm);
}


void mainWindow::openDSM()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open DSM"), "" , tr("DSM files (*.dsm);;All files (*.*)"));
    QFile fin(fileName);
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text))
         return;
// 여기부터는 dsmModel에서 처리
    QString a = fin.readLine();
    int num = a.toInt();

    DsmModel* dsm = new DsmModel(num);

    for (int i = 0; i < num; i++) {
        a = fin.readLine();
        for (int j = 0; j < num; j++) {
            QStandardItem* item = new QStandardItem(a.mid(j*2, 1));
            dsm->setItem(i, j, item);
        }
    }
    for (int i = 0; i < num; i++) {
        a = fin.readLine();
        QStandardItem* item = new QStandardItem(a);
        dsm->setVerticalHeaderItem(i, item);
    }
    //
    ui->tableView->setModel(dsm);
    fin.close();
}


void mainWindow::saveDSM()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save DSM"), tr("out.dsm"), tr("DSM files (*.dsm)"));
    QFile fout(fileName);
    if (!fout.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
//여기부터는 dsmModel에서 처리
    DsmModel* dsm = new DsmModel(3);
    dsm->setRowCount(3);
    dsm->setColumnCount(3);
    for (int i = 0; i < 3; i++) {
        QStandardItem* item1 = new QStandardItem("2");
        dsm->setItem(i, 0, item1);
        QStandardItem* item2 = new QStandardItem("0");
        dsm->setItem(i, 1, item2);
        QStandardItem* item3 = new QStandardItem("1");
        dsm->setItem(i, 2, item3);
        QStandardItem* item = new QStandardItem("a");
        dsm->setVerticalHeaderItem(i, item);
    }
    ui->tableView->setModel(dsm);

    QString result = QString::number(dsm->rowCount());
    fout.write(result.toLocal8Bit());
    for (int i = 0; i < dsm->rowCount(); i++) {
        result = "\n";
        for (int j = 0; j < dsm->columnCount(); j++) {
            result += dsm->item(i, j)->text();
            if (j < dsm->rowCount()-1)
                result += " ";
        }
        fout.write(result.toLocal8Bit());
    }
    for (int i = 0; i < dsm->rowCount(); i++) {
        result = "\n";
        result += dsm->verticalHeaderItem(i)->text();
        fout.write(result.toLocal8Bit());
    }
    //
    fout.close();
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
    QFile fin(fileName);
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text))
         return;
// 여기부터는 clusterModel에서 처리
//    qDebug()<<fin.readLine();
    if (fin.readLine() != "<cluster>\n")
        return;
    QStandardItemModel* clm = new QStandardItemModel();
    QStandardItem* root = clm->invisibleRootItem();
    QStandardItem* cur = root;
    QStandardItem* item;
    while (!fin.atEnd()) {
        QString a = fin.readLine();
        if (a.left(13)=="<group name=\"") {
            item = new QStandardItem(a.mid(13, a.size()-16));
            cur->appendRow(item);
            cur = item;
        } else if (a.left(12) == "<item name=\"") {
            item = new QStandardItem(a.mid(12, a.size()-17));
            cur->appendRow(item);
        } else if (a == "</group>\n") {
            cur = static_cast<QStandardItem*>(cur->parent());
        } else if (a == "</cluster>\n") {
            ;
        }
    }
    ui->treeView->setModel(clm);
    fin.close();
}


void mainWindow::saveClustering()
{
    QString fileName2 = QFileDialog::getOpenFileName(this, tr("Open Clustering"), "" , tr("Cluster files (*.clsx);;All files (*.*)"));
    QFile fin(fileName2);
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text))
         return;
// 여기부터는 clusterModel에서 처리
//    qDebug()<<fin.readLine();
    if (fin.readLine() != "<cluster>\n")
        return;
    QStandardItemModel* clm = new QStandardItemModel();
    QStandardItem* root = clm->invisibleRootItem();
    QStandardItem* cur2 = root;
    QStandardItem* item;
    while (!fin.atEnd()) {
        QString a = fin.readLine();
        if (a.left(13)=="<group name=\"") {
            item = new QStandardItem(a.mid(13, a.size()-16));
            cur2->appendRow(item);
            cur2 = item;
        } else if (a.left(12) == "<item name=\"") {
            item = new QStandardItem(a.mid(12, a.size()-17));
            cur2->appendRow(item);
        } else if (a == "</group>\n") {
            cur2 = static_cast<QStandardItem*>(cur2->parent());
        } else if (a == "</cluster>\n") {
            ;
        }
    }
    ui->treeView->setModel(clm);

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Clustering"), tr("out.clsx"), tr("Cluster files (*.clsx)"));
    QFile fout(fileName);
    if (!fout.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QString result = "<cluster>";
    fout.write(result.toLocal8Bit());
    QStandardItem* cur = clm->invisibleRootItem()->child(0, 0);
    int i = 0;
    while (i < 10) {
        result = "\n";
        if (cur->hasChildren()) {
            result += "<group name=\"";
            result += cur->text();
            result += "\">";
            cur = cur->child(0, 0);
        } else {
            result += "<item name=\"";
            result += cur->text();
            result += "\" />";
        }
        fout.write(result.toLocal8Bit());
        i++;
    }
    fout.close();
}


void mainWindow::saveAsClustering()
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

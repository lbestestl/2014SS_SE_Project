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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open DSM"), "" , tr("Design structure matrix files (*.dsm);;All files (*.*)"));
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
    QString fileName = QFileDialog::getSaveFileName(this, tr("save DSM"), tr("out.dsm"), tr(".dsm (*.dsm)"));
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
    for (int i = 0; i < dsm->rowCount(); i++) {
        result += "\n";
        for (int j = 0; j < dsm->columnCount(); j++) {
            result += dsm->item(i, j)->text();
            if (j < dsm->rowCount()-1)
                result += " ";
        }
    }
    for (int i = 0; i < dsm->rowCount(); i++) {
        result += "\n";
        result += dsm->verticalHeaderItem(i)->text();
    }
    fout.write(result.toLocal8Bit());
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
    ui->treeWidget->expandAll();
}


void mainWindow::collapseAll()
{
    ui->treeWidget->collapseAll();
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

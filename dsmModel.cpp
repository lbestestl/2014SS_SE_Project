#include "dsmModel.h"

#include <QFile>


DsmModel::DsmModel(int num)
    : QStandardItemModel(num, num)
{
//    dsmModel = new QStandardItemModel(num, num);
}


DsmModel::~DsmModel()
{
//    delete dsmModel;
}


void DsmModel::store(QString fileName)
{
    if (fileName == NULL)
        return;
    QFile* fout = new QFile(fileName);
    if (!fout->open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QString result = QString::number(this->rowCount());
    fout->write(result.toLocal8Bit());
    for (int i = 0; i < this->rowCount(); i++) {
        result = "\n";
        for (int j = 0; j < this->columnCount(); j++) {
            result += this->item(i, j)->text();
            if (j < this->rowCount()-1)
                result += " ";
        }
        fout->write(result.toLocal8Bit());
    }
    for (int i = 0; i < this->rowCount(); i++) {
        result = "\n";
        result += this->verticalHeaderItem(i)->text();
        fout->write(result.toLocal8Bit());
    }
    fout->close();
    delete fout;
}


void DsmModel::load(QString fileName)
{
    if (fileName == NULL)
        return;
    QFile* fin = new QFile(fileName);
    if (!fin->open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString a = fin->readLine();
    int num = a.toInt();

    for (int i = 0; i < num; i++) {
        a = fin->readLine();
        for (int j = 0; j < num; j++) {
            QStandardItem* item = new QStandardItem(a.mid(j*2, 1));
            this->setItem(i, j, item);
        }
    }
    for (int i = 0; i < num; i++) {
        a = fin->readLine();
        QStandardItem* item = new QStandardItem(a.simplified());
        this->setVerticalHeaderItem(i, item);
    }
    fin->close();
    delete fin;
}


void DsmModel::deleteAll()
{
    for (int i = 0; i < this->rowCount(); i++) {
        for (int j = 0; j < this->rowCount(); j++) {
            delete this->takeItem(i, j);
        }
    }
    for (int i = 0; i < this->rowCount(); i++) {
        delete this->takeVerticalHeaderItem(i);
    }
    this->clear();
}


void DsmModel::appendEntity()
{
    int n = this->rowCount();

    QList<QStandardItem*> row;
    for (int i = 0; i < this->rowCount(); i++) {
        QStandardItem* item = new QStandardItem("0");
        row.append(item);
    }
    this->insertRow(n, row);

    QList<QStandardItem*> col;
    for (int i = 0 ; i < this->rowCount(); i++) {
        QStandardItem* item = new QStandardItem("0");
        col.append(item);
    }
    this->insertColumn(n, col);

    QStandardItem *item = new QStandardItem(QString::number(n+1));
    this->setVerticalHeaderItem(n, item);
}

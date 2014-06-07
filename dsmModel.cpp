#include "dsmModel.h"
#include <QDebug>
#include <QFile>


DsmModel::DsmModel(int num)
    : QStandardItemModel(num, num)
{
}


DsmModel::~DsmModel()
{

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


//void DsmModel::group(QItemSelectionModel*)
//{
//}


//void DsmModel::ungroup(QItemSelectionModel*)
//{
//}

//void DsmModel::moveUp(QItemSelectionModel*)
//{
//}


//void DsmModel::moveDown(QItemSelectionModel*)
//{
//}


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


void DsmModel::deleteEntity(QItemSelectionModel* sm)
{
    for (int j = 0; j < sm->selectedIndexes().count(); j++) {
        int num = -1;
        for (int i = 0; i < this->rowCount(); i++) {
            if (this->verticalHeaderItem(i)->text() == sm->selectedIndexes().at(j).data().toString())
                num = i;
        }
        if (num == -1)
            continue;

        for (int i = 0; i < this->columnCount(); i++) {
            delete this->takeItem(num, i);
        }
        delete this->takeVerticalHeaderItem(num);
        for (int i = 0; i < this->rowCount(); i++) {
            if (i != num)
                delete this->takeItem(i, num);
        }
        delete this->takeHorizontalHeaderItem(num);
        this->takeRow(num);
        this->takeColumn(num);
    }
}


int DsmModel::findVerticalHeaderItem(QString text)
{
    for (int i = 0; i < this->rowCount(); i++)
        if (text == this->verticalHeaderItem(i)->text())
            return i;
    return -1;
}

#include "clusterModel.h"


ClusterModel::ClusterModel()
    : QStandardItemModel()
{
}


ClusterModel::~ClusterModel()
{
}


void ClusterModel::search(QFile* fout, QStandardItem* cur, int n)
{
    QStandardItem* par = static_cast<QStandardItem*>(cur->parent());

    for (int i = 0; i < n; i++) {
        QString result ="\n";
        if (cur->hasChildren()) {
            result += "<group name=\"";
            result += cur->text();
            result += "\">";
            fout->write(result.toLocal8Bit());
            search(fout, cur->child(0, 0), cur->rowCount());
            result = "\n</group>";
            fout->write(result.toLocal8Bit());
        } else {
            result += "<item name=\"";
            result += cur->text();
            result += "\" />";
            fout->write(result.toLocal8Bit());
        }
        if (i < n-1)
            cur = par->child(i+1, 0);
    }
    cur = par;
}


void ClusterModel::store(QString fileName)
{
    QFile* fout = new QFile(fileName);
    if (!fout->open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QString result = "<cluster>";
    fout->write(result.toLocal8Bit());
    QStandardItem* cur = this->invisibleRootItem();
    search(fout, cur->child(0,0), cur->rowCount());
    result = "\n</cluster>";
    fout->write(result.toLocal8Bit());
    fout->close();
    delete fout;
}


void ClusterModel::load(QString fileName)
{
    QFile* fin = new QFile(fileName);
    if (!fin->open(QIODevice::ReadOnly | QIODevice::Text))
         return;

    if (fin->readLine() != "<cluster>\n")
        return;

    QStandardItem* cur = this->invisibleRootItem();
    QStandardItem* item;
    while (!fin->atEnd()) {
        QString a = fin->readLine();
        if (a.left(13)=="<group name=\"") {
            item = new QStandardItem(a.mid(13, a.size()-16));
            cur->appendRow(item);
            cur = item;
        } else if (a.left(12) == "<item name=\"") {
            item = new QStandardItem(a.mid(12, a.size()-17));
            item->setEditable(false);
            cur->appendRow(item);
        } else if (a == "</group>\n") {
            cur = static_cast<QStandardItem*>(cur->parent());
        } else if (a == "</cluster>\n") {
            ;
        } else {
            ;//error
        }
    }
    fin->close();
    delete fin;
}


void ClusterModel::deleteAll()
{
//    QStandardItem* cur = this->invisibleRootItem();
//    cur->hasChildren()
    this->clear();
}

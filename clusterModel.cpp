#include "clusterModel.h"
#include <QDebug>

ClusterModel::ClusterModel()
    : QStandardItemModel()
{
}


ClusterModel::~ClusterModel()
{
}


//store에서 사용하는 recursive function.
void ClusterModel::internalStore(QFile* fout, QStandardItem* cur, int n)
{
    QStandardItem* par = static_cast<QStandardItem*>(cur->parent());

    for (int i = 0; i < n; i++) {
        QString result ="\n";
        if (cur->hasChildren()) {
            result += "<group name=\"";
            result += cur->text();
            result += "\">";
            fout->write(result.toLocal8Bit());
            internalStore(fout, cur->child(0, 0), cur->rowCount());
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


//지정된 file에 저장
void ClusterModel::store(QString fileName)
{
    QFile* fout = new QFile(fileName);
    if (!fout->open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QString result = "<cluster>";
    fout->write(result.toLocal8Bit());
    QStandardItem* cur = this->invisibleRootItem();
    if (!cur->hasChildren())
        return;
    internalStore(fout, cur->child(0,0), cur->rowCount());
    result = "\n</cluster>";
    fout->write(result.toLocal8Bit());
    fout->close();
    delete fout;
}


//지정된 file로 부터 불러오기
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


//DsmModel로 부터 clusterModel 생성
void ClusterModel::load(DsmModel *model)
{
    QStandardItem* cur = this->invisibleRootItem();
    QStandardItem* item = new QStandardItem("$root");
    cur->appendRow(item);
    cur = item;
    for (int i = 0; i < model->rowCount(); i++) {
        item = new QStandardItem(model->verticalHeaderItem(i)->text());
        item->setEditable(false);
        cur->appendRow(item);
    }
}


//deleteAll에서 사용하는 recursive function
void ClusterModel::internalDelete(QStandardItem* cur)
{
    if (cur == NULL)
        return;
    int count = cur->rowCount();
    for (int i = 0; i < count; i++) {
        internalDelete(cur->child(i, 0));
    }
    delete cur;
}


//cluster model의 자원을 모두 해제함.
void ClusterModel::deleteAll()
{
    internalDelete(this->invisibleRootItem());
    this->clear();
}


//view에서 선택된 것들을 group화
void ClusterModel::group(QItemSelectionModel *sm)
{
    QStandardItem* cur = this->itemFromIndex(sm->selectedIndexes().first());
    QStandardItem* par = static_cast<QStandardItem*>(cur->parent());
    if (par == NULL)
        return;
    cur = new QStandardItem("group");
    cur->setEditable(true);
    par->insertRow(sm->selectedIndexes().first().row(), cur);

    int count = sm->selectedIndexes().count();
    for (int i = 0; i < count ; i++) {
        QList<QStandardItem*> item = par->takeRow(this->itemFromIndex(sm->selectedIndexes().first())->row());
        cur->appendRow(item);
    }
}


//view에서 선택된 것들을 ungroup
void ClusterModel::ungroup(QItemSelectionModel *sm)
{
    int count = sm->selectedIndexes().count();
    for (int i = 0; i < count; i++) {
        QStandardItem* cur = this->itemFromIndex(sm->selectedIndexes().takeFirst());
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


//view에서 선택된 것들을 위로 이동
void ClusterModel::moveUp(QItemSelectionModel *sm)
{
    int count = sm->selectedIndexes().count();
    for (int i = 0; i < count; i++) {
        QStandardItem* cur = this->itemFromIndex(sm->selectedIndexes().at(0));
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


//view에서 선택된 것들을 아래로 이동
void ClusterModel::moveDown(QItemSelectionModel *sm)
{
    int count = sm->selectedIndexes().count();
    for (int i = 0; i < count; i++) {
        QStandardItem* cur = this->itemFromIndex(sm->selectedIndexes().at(count-1-i));
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


//n번째 개체 추가
void ClusterModel::appendEntity(int n)
{
    QStandardItem* item = new QStandardItem(QString::number(n));
    item->setEditable(false);
    if (!this->invisibleRootItem()->hasChildren()) {
        QStandardItem* root = new QStandardItem("$root");
        this->invisibleRootItem()->appendRow(root);
    }
    this->invisibleRootItem()->child(0)->appendRow(item);
}

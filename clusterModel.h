#ifndef CLUSTERMODEL_H
#define CLUSTERMODEL_H


#include <QStandardItemModel>
#include <QFile>


class ClusterModel
    : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit ClusterModel();
    ~ClusterModel();
    void store(QString fileName);
    void load(QString fileName);

private:
    void search(QFile* fout, QStandardItem* cur, int n);
};


#endif // CLUSTERMODEL_H

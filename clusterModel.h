#ifndef CLUSTERMODEL_H
#define CLUSTERMODEL_H


#include "projectModel.h"

#include <QItemSelectionModel>
#include <QFile>


class ClusterModel
    : public ProjectModel
{
    Q_OBJECT

public:
    explicit ClusterModel();
    ~ClusterModel();
    void deleteAll();
    void store(QString fileName);
    void load(QString fileName);
    void load(ProjectModel *);

    void group(QItemSelectionModel*);
    void ungroup(QItemSelectionModel*);
    void moveUp(QItemSelectionModel*);
    void moveDown(QItemSelectionModel*);
    void appendEntity(int n = 0);
    void deleteEntity(QItemSelectionModel*);

private:
    void internalStore(QFile*, QStandardItem* , int rowCount);
    void internalDelete(QStandardItem*);
};


#endif // CLUSTERMODEL_H

#ifndef DSMMODEL_H
#define DSMMODEL_H


#include "projectModel.h"


class DsmModel
    : public ProjectModel
{
    Q_OBJECT

public:
    explicit DsmModel(int numOfData = 0);
    ~DsmModel();
    void deleteAll();
    void store(QString fileName);
    void load(QString fileName);
    void appendEntity();
    void deleteEntity(QItemSelectionModel*);
    int findVerticalHeaderItem(QString text);
};


#endif // DSMMODEL_H

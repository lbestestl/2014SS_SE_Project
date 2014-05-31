#ifndef DSMMODEL_H
#define DSMMODEL_H


#include <QStandardItemModel>


class DsmModel
    : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit DsmModel(int numOfData = 0);
    ~DsmModel();
    void deleteAll();
    void store(QString fileName);
    void load(QString fileName);
    void appendEntity();
    void deleteEntitiy();
};


#endif // DSMMODEL_H

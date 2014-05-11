#ifndef DSMMANAGE_H
#define DSMMANAGE_H


#include <QStandardItemModel>


class DsmModel
    : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit DsmModel(int numOfData = 0);
    ~DsmModel();
    void store();
    void load();
};


#endif // DSMANAGE_H

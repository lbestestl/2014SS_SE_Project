#ifndef PROJECTMODEL_H
#define PROJECTMODEL_H


#include <QStandardItemModel>
#include <QItemSelectionModel>


class ProjectModel
        : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit ProjectModel();
    explicit ProjectModel(int);
    virtual ~ProjectModel();

    void deleteAll();
    void store(QString fileName);
    void load(QString fileName);
    void appendEntity();
    void deleteEntity(QItemSelectionModel*);
};

#endif // PROJECTMODEL_H

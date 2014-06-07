#include "projectModel.h"


ProjectModel::ProjectModel()
    : QStandardItemModel()
{
}


ProjectModel::ProjectModel(int n)
    : QStandardItemModel(n, n)
{
}


ProjectModel::~ProjectModel()
{
}

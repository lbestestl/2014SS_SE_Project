#ifndef GLOBALINST_H
#define GLOBALINST_H


#include "clusterModel.h"
#include "dsmModel.h"


class GlobalInst
{
public:
    GlobalInst();
private:
    ClusterModel* clm;
    DsmModel* dsm;
    bool isModified;
    //this class will be singleton.
};

#endif // GLOBALINST_H

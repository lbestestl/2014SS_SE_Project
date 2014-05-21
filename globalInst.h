#ifndef GLOBALINST_H
#define GLOBALINST_H


#include "clusterModel.h"
#include "dsmModel.h"


class GlobalInst
{
public:
    static GlobalInst* getInstance()
    {
        if (inst == NULL)
            inst = new GlobalInst();
        return inst;
    }
    ClusterModel* clm;
    DsmModel* oriDsm;
    DsmModel* curDsm;
    bool dsmExist;
    bool dsmModified;
    bool clmModified;
    QString dsmPath;
    QString clmPath;

private:
    GlobalInst();
    ~GlobalInst();
    static GlobalInst* inst;
};


#endif // GLOBALINST_H

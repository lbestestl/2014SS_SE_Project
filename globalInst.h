#ifndef GLOBALINST_H
#define GLOBALINST_H


#include "clusterModel.h"
#include "dsmModel.h"


class GlobalInst
{
public:
    static inline GlobalInst* getInstance()
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
    QString dsmPath;
    bool clmModified;
    QString clmPath;

private:
    GlobalInst();
    ~GlobalInst();
    static GlobalInst* inst;
};


void clearDsm();
void clearClm();


#endif // GLOBALINST_H

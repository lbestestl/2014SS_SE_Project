#include "globalInst.h"


GlobalInst* GlobalInst::inst = NULL;


GlobalInst::GlobalInst()
    : clm(NULL), oriDsm(NULL), curDsm(NULL),
      dsmExist(false),
      dsmModified(false), dsmPath(""),
      clmModified(false), clmPath("")
{
}


GlobalInst::~GlobalInst()
{
}


//dsm model의 자원을 해제하고 global변수를 조정
void clearDsm()
{
    if (GlobalInst::getInstance()->dsmExist) {
        GlobalInst::getInstance()->oriDsm->deleteAll();
        delete GlobalInst::getInstance()->oriDsm;
        GlobalInst::getInstance()->oriDsm = NULL;
        GlobalInst::getInstance()->curDsm->deleteAll();
        delete GlobalInst::getInstance()->curDsm;
        GlobalInst::getInstance()->curDsm = NULL;
        GlobalInst::getInstance()->dsmExist = false;
        GlobalInst::getInstance()->dsmPath = "";
        GlobalInst::getInstance()->dsmModified = false;
    }
}


//cluster model의 자원을 해제하고 global변수를 조정
void clearClm()
{
    if (GlobalInst::getInstance()->clm != NULL) {
        GlobalInst::getInstance()->clm->deleteAll();
        delete GlobalInst::getInstance()->clm;
        GlobalInst::getInstance()->clm = NULL;
        GlobalInst::getInstance()->clmPath = "";
        GlobalInst::getInstance()->clmModified = false;
    }
}

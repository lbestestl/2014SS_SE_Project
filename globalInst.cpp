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

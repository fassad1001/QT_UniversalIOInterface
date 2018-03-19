#include <stdio.h>
#include <stdlib.h>

//#include "global.h"
#include "pluging.h"
#include <QString>

//#include "cmain.h"

int  __PLUGID_M = 0;

CBasePlugClass::CBasePlugClass(QObject *parent)
{    
    INITPLUG((char *)"BasePlug", 0);

    ppm = NULL;
    showAct = NULL;
    pmain = NULL;

    CR_LINK(ptrPlugInit, CBasePlugClass, this, QString("PlugInit"), &CBasePlugClass::_PlugInit, SPlugMenu *);
    CR_LINK(ptrPlugDrop, CBasePlugClass, this, QString("PlugDrop"), &CBasePlugClass::_PlugDrop, void*, uint);

    CR_LINK(ptrArmPD, CBasePlugClass, this, QString("ArmPlugDetail"), &CBasePlugClass::ArmPlugDetail, uint);
    CR_LINK(ptrSetPlugID, CBasePlugClass, this, QString("SetPlugID"), &CBasePlugClass::_SetPlugID, void*, uint);
    CR_LINK(ptrSetDBObj,  CBasePlugClass, this, QString("SetDBObj"),  &CBasePlugClass::_SetDBObj, void*);



    connect( this, SIGNAL(sigPlugDetail( SPlugDetail, uint )), parent, SLOT(PlugDetail( SPlugDetail, uint)) );    
}

void CBasePlugClass::ArmPlugDetail(uint id){
    emit sigPlugDetail(pd, id);
}

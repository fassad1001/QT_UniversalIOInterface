#ifndef CPLUGING_H
#define CPLUGING_H
/**
		@author Sokolov Alexander
*/

#include "../include/def.h"
#include "../include/plugcmdlist.h"
#include <QDialog>
#include <QObject>
#include <QMap>

#define MENU_TEST 1L

class CBasePlugClass : public _TADRR
{
    Q_OBJECT
public:
    explicit CBasePlugClass(QObject *parent = NULL);

    SPlugDetail pd;
    SPlugMenu *ppm;
    QAction   *showAct;

    virtual void SetPlugID(void*, uint){}
    virtual void PlugInit(){}
    virtual void PlugDrop(void*, uint){}
    virtual void SetDBObj(void *){}
private:	        
    void _SetDBObj(void *obj){SetDBObj(obj);}
    void _SetPlugID(void*obj, uint id){SetPlugID(obj, id);}
    void _PlugInit(SPlugMenu *pm){ppm=pm;PlugInit();}
    void _PlugDrop(void* obj, uint id){PlugDrop(obj, id);}

    defPostPtrFunc2(CBasePlugClass, TPlugInit, ptrPlugInit, SPlugMenu *)
    defPostPtrFunc2(CBasePlugClass, TPlugDrop, ptrPlugDrop, void*, uint)

    defPostPtrFunc2(CBasePlugClass, TArmPD, ptrArmPD, uint)
    defPostPtrFunc2(CBasePlugClass, TPlugID, ptrSetPlugID, void*, uint)
    defPostPtrFunc2(CBasePlugClass, TPlugDBObj, ptrSetDBObj, void*)

    void *pmain;
    void  ArmPlugDetail(uint);
signals:
    void sigPlugDetail( SPlugDetail pd, uint id );    

};

#define INITPLUG( description, id ) pd.SPlugDetailChange( (char*)description, id ); extern int __PLUGID_M; __PLUGID_M = id

#endif

#ifndef PLUGCMDLIST_H
#define PLUGCMDLIST_H

#define SETCALLBACK 1L

///Получить указатель на объект
#define GET_PLUGING_BY_ID   4L

#include <QMainWindow>
#include <QMenuBar>
///Pluging detail here
#define PLUGDETAIL 2L
#include <QWidget>
#include <QAction>
#include <QMenu>
#include <QGridLayout>

#define PLUGID     1000L
#define DROP_PLUG  999L
#define SETDBOPTIONS 5L
#define DBOBJ      1001L

//**************************
///using for graph plug
#define GETGRAPHMODULES 7L
#define GETGRAPHMODULES_ID 8L
//Needed for pojection search in 2 gl stream
#define CTRLRENDER 9L
//**************************

#define ON_CLOSE 8L

#include "def.h"
#include "usermsgtemplate.h"
#include "dll_linker.h"

/*class CPlugList;
typedef SingularCallBack < CPlugList, void, uint, BYTE*, uint, uint > AToMainThreadMessage;*/


class CPluging;
typedef CDllLink < CPluging > pdp_dll;

#define defPostPtrFunc( TeasyPTR, f, args ... ) \
    typedef SUniPtr<easyT<CPluging, args>> TeasyPTR; \
    TeasyPTR f;

#define defPostPtrFunc2(Class, TeasyPTR, f, args ... ) \
    typedef SUniPtr<easyT<Class, args>> TeasyPTR; \
    TeasyPTR f;
#define defPostPtrFuncA2(Class, TeasyPTR, f ) \
    typedef SUniPtr<easyT<Class>> TeasyPTR; \
    TeasyPTR f;

#define createPostPtrFunc( function, FUNC_ID, args ... ) \
    function.clear();\
    function = (easyT<CPluging, args>*)((pdp_dll*)data)->CallMessage(FUNC_ID, 0, 0, 0)
#define createPostFunc(Class, ClassObj, Func, args ...) new easyT<Class, args>(Func, (Class*)ClassObj)

#define createPostFuncA(Class, ClassObj, Func) new easyT<Class>(Func, (Class*)ClassObj)

#define CP_PTR(ptr, Class, ptr_addr, args ...) ptr = *((SUniPtr<easyT<Class, args>>*)ptr_addr);
#define CR_LINK(SafePtr, Class, Obj, funcName, funcPtr, args ... ) \
SafePtr = createPostFunc(Class, Obj, funcPtr, args); \
AddAddrByName(funcName.toStdString().c_str(), (void*)&SafePtr);

struct __spair{
    __spair(const char *__key, void* __addr){
        strcpy(FuncName, __key);
        addr = __addr;
    }
    void* contains(const char *key){
        if (!strcmp(FuncName, key)) return addr;
        return NULL;
    }

    char FuncName[32];
    void* addr;
};

//static int a = 666;
class _TADRR : public QObject{
public:
        _TADRR() : QObject() {}
        void* GetAddrByName(const char* key){
            void *ret_addr = NULL;
            for (std::vector<__spair>::iterator it = map_addr.begin(); it != map_addr.end(); ++it)                
                if ((ret_addr = it->contains(key))) return ret_addr;

            return NULL;
        }
        void  AddAddrByName(const char* key, void *addr){            
            map_addr.push_back(__spair(key, addr));            
            qDebug("add");
        }

   std::vector<__spair> map_addr;
};

struct SPlugDetail{
    SPlugDetail(){
        strcpy(Description, "My Test pluging");
        plugid = 1L;
    };
    SPlugDetail(char description[64], uint id){
        strcpy(Description, description);
        plugid = id;
    };
    void SPlugDetailChange(char description[64], uint id){
        strcpy(Description, description);
        plugid = id;
    };

    char Description[64];
    unsigned int plugid;
};

///end of plug detail


///Menu messages
#define PLUG_INIT          1999L

#ifndef __MYWIDGET
#define __MYWIDGET
typedef struct SMyWidget{
public:
    SMyWidget( void *_pObj, uint _id, uint _plugid){
     pObj = _pObj;
     id = _id;
     plugid = _plugid;
    }

    void  * pObj;
    uint    id;
    uint    plugid;
}TMyWidget;
#endif

typedef std::vector <TMyWidget> TVECMYWIDGET;

struct SPlugMenu{
    SPlugMenu(){
      pWindow = NULL;
      pmenu   = NULL;
      pObj = NULL;
      hMenu = NULL;
    }
    SPlugMenu( char menu_item_name[64], uint menu_item_id ){
        strcpy(chMenuItemName, menu_item_name);
        uiMenuItemId = menu_item_id;
        pWindow = NULL;
        pmenu   = NULL;
        pObj = NULL;
        hMenu = NULL;
    }

    char chMenuItemName[64];
    unsigned int uiMenuItemId;

    //QMainWindow *pmw;
    QMenu    *pmenu;
    QObject  *pObj;
    QWidget  *pWindow;
    void     *hMenu;
    TVECMYWIDGET vecWidgets;
};

///*************


template <typename ... types>
struct TPlugsCB{    
    typedef SUniPtr<easyT<CPluging, types ...>> TeasyPTR;

    TPlugsCB() : sm(1){}

    void NewCB( uint plugID, void* f ){
        if (!cbPair.contains(plugID)){
            sm++;
            cbPair[plugID] = (easyT<CPluging, types ...>*)f;
            sm--;
        }
    }

    void FreeCB( uint plugID ){
        sm++;
        qDebug("FreeCB for plug %d = %d", plugID, cbPair.remove(plugID));
        sm--;
    }


    void AddPostEvent( types ... args ){
        sm++;
        foreach( TeasyPTR ptr, cbPair.values()) ptr->AddPostEvent( args ... );
        sm--;
    }

    void Execute( types ... args ){
        sm++;
        foreach( TeasyPTR ptr, cbPair.values()) ptr->Execute( args ... );
        sm--;
    }

    void AddPostEvent( int plugID, types ... args ){
        sm++;
        if (cbPair.contains(plugID))
            cbPair.value( plugID )->AddPostEvent( args ... );
        sm--;
    }

    TeasyPTR GetObj( int plugID ){
        return cbPair.value( plugID );
    }

    bool IsObjContains( int plugID ){ return cbPair.contains( plugID ); }

    void Clear() {
        sm++;
        cbPair.clear();
        sm--;
    }

    void DieAll() {
        sm++;
        foreach (TeasyPTR t, cbPair) t->getObj()->die();
        sm--;
    }
    size_t size(){
        return cbPair.size();
    }

    private:
    QMap<int, TeasyPTR> cbPair;
    QMySemaphore sm;
};


template <typename t>
struct _REF{
    _REF() : sm(1){ sm++; }
    ~_REF(){
        sm--;
    }
    _REF( t v ) : sm(1){ _val = v; sm++;}
    t &operator = ( t &v ){ _val = v; return _val; }
    void unsync( t v ) { _val = v; if (!sm.available()) sm--; }
    void unsync() { if (!sm.available()) sm--; }
    void sync( t v ) { _val = v; sm++; }
    void sync() { sm++; }
    t & operator ++ ( int ){ sm++; return _val; }
    t & operator -- ( int ){ sm--; return _val; }
    t val(){ return _val; }
    void set( t v ){ _val = v; }
private:
    t _val;
    QMySemaphore sm;
};

typedef _REF<bool> R_BOOL;
typedef _REF<int > R_INT;
typedef _REF<QString> R_QString;


#endif // PLUGCMDLIST_H



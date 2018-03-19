#ifndef POSTDEF_H
#define POSTDEF_H

#include "../defines/usermsgtemplate.h"
#include "../defines/dll_linker.h"
#include <QDebug>
class CPlugList;
typedef SingularCallBack < CPlugList, void, uint, BYTE*, uint, uint > AToMainThreadMessage;

class CPluging;
typedef CDllLink < CPluging > pdp_dll;

#define defPostPtrFunc1( TeasyPTR, args ... ) typedef SUniPtr<easyT<CPluging, args>> TeasyPTR;
#define defPostPtrFuncA1( Class, TeasyPTR, args ... )  typedef SUniPtr<easyT<Class, args>> TeasyPTR;

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

#define convertType(Class, ClassObj) *(Class*)&ClassObj

struct SPlugDetail{
    SPlugDetail(){
        strcpy(Description, "My Test pluging");
        plugid = 1L;
    }
    SPlugDetail(char description[64], uint id){
        strcpy(Description, description);
        plugid = id;
    }
    void SPlugDetailChange(char description[64], uint id){
        strcpy(Description, description);
        plugid = id;
    }

    char Description[64];
    unsigned int plugid;
};


template<typename key, class CPrototype, typename ... types>
struct TPlugsCB{    
    typedef SUniPtr<easyT<CPrototype, types ...>> TeasyPTR;

    TPlugsCB() : sm(1){}

    void NewCB( key plugID, TeasyPTR ptr ){
        //sm++;
        cbPair[plugID] = ptr;
        //sm--;
    }

    void FreeCB( key plugID ){
        //sm++;
        plugForRemove = plugID;
        cbPair.remove(plugID);
        //qDebug() << "Free callback" << plugID;
        //sm--;
    }
    
    bool IsRemoving( key plugID ){
        return (plugForRemove == plugID) ? true : false;
    }


    void AddPostEvent( types ... args ){
        //sm++;      
        foreach( TeasyPTR ptr, cbPair.values()) ptr->AddPostEvent( args ... );
        //sm--;
    }

    void Execute( types ... args ){
        //sm++;
        foreach( TeasyPTR ptr, cbPair.values()) ptr->Execute( args ... );
        //sm--;
    }

    void AddPostEvent( key plugID, types ... args ){
        //sm++;
        if (cbPair.contains(plugID))
            cbPair.value( plugID )->AddPostEvent( args ... );
        //sm--;
    }

    TeasyPTR LockObj( key plugID ){
        //sm++;
        return cbPair.value( plugID );
    }
    void UnlockObj(){ /*sm--;*/ }
    

    bool IsObjContains( key plugID ){
      //sm++;
      bool val = cbPair.contains( plugID );
      //sm--;
      return val;
    }

    void Clear() {
        //sm++;
        cbPair.clear();
       //sm--;
    }

    void DieAll() {
        //sm++;
        foreach (TeasyPTR t, cbPair) t->getObj()->die();
        //sm--;
    }
    size_t GetCount(){
      return cbPair.size();
    }
    private:
    key plugForRemove;
    QMap<key, TeasyPTR> cbPair;
    QMySemaphore sm;
};


template <class key, class classname, typename ... types>
struct TCB_PTR{
    typedef SUniPtr<easyT<classname, types ...>> TeasyPTR;

    TCB_PTR() : sm(1){}

    void NewCB( key plugID, TeasyPTR ptr ){
        //sm++;
        cbPair[plugID] = ptr;
        //sm--;
    }

    void FreeCB( key plugID ){
        //sm++;
        qDebug() << "FreeCB for plug" << plugID;
        plugForRemove = plugID;
        cbPair.remove(plugID);
        //sm--;
    }


    void AddPostEvent( types ... args ){
        //sm++;
        foreach( TeasyPTR ptr, cbPair.values()) ptr->AddPostEvent( args ... );
        //sm--;
    }

    void Execute( types ... args ){
        //sm++;
        foreach( TeasyPTR ptr, cbPair.values()) ptr->Execute( args ... );
        //sm--;
    }

    void AddPostEvent( key plugID, types ... args ){
        //sm++;
        if (cbPair.contains(plugID))
            cbPair.value( plugID )->AddPostEvent( args ... );
        //sm--;
    }
    void Execute( key plugID, types ... args ){
        //sm++;
        if (cbPair.contains(plugID))
            cbPair.value( plugID )->Execute( args ... );
        //sm--;
    }

    /*TeasyPTR GetObj( key plugID ){
        sm++;
        TeasyPTR ptr = cbPair.value( plugID );
        sm--;
        return ptr;
    }*/

    bool IsRemoving( key plugID ){
        return (plugForRemove == plugID) ? true : false;
    }

    bool IsObjContains( key plugID ){
        //sm++;
        bool val = cbPair.contains( plugID );
        //sm--;
        return val;
    }
    QList<key> GetKeys() {
        //sm++;
        QList<key> list = cbPair.keys();
        //sm--;
        return list;
    }

    void Clear() {
        DieAll();

        //sm++;
        cbPair.clear();
        //sm--;
    }

    void DieAll() {
        //sm++;
        foreach (TeasyPTR t, cbPair) t->getObj()->die();
        //sm--;
    }
    private:
    QMap<key, TeasyPTR> cbPair;
    QMySemaphore sm;
    volatile key plugForRemove;
};

template <typename ... types> struct TPlugsCB_PTR : TCB_PTR<uint, CPluging, types ...>{};


template<class Key, class T>
class QMapSync{
public:
      QMapSync() : sm(1){}

      void remove ( Key key ){
          sm++;
          map.remove( key );
          sm--;
      }

      bool getValueByKey(Key key, T &_t){
          sm++;
          if (map.contains(key)){
              _t = map[key];
              sm--;
              return true;
          }else{
             sm--;
              return false;
          }
          sm--;
      }
      bool getKeyByValue(Key &key, T _t){
          for(auto it = map.begin(); it != map.end(); ++it)
          if (it.value() == _t){
              key = it.key();
              return true;
          }
          return false;
      }
      bool eraseByValue( T _t ){
          sm++;
          for(auto it = map.begin(); it != map.end(); ++it)
          if (it.value() == _t){
              map.erase(it);
              sm--;
              return true;
          }
          sm--;
          return false;
      }

      void clear(){
          sm++;
          map.clear();
          sm--;
      }

      /*T &operator[](const Key &key){
        return map[key];
      }*/

      const T operator[](const Key &key){
          sm++;
          QMap<Key, T> _map = map;
          sm--;
          return _map.value(key);
      }

      void addKey(Key key, T _t){
          sm++;
          map[key] = _t;
          sm--;
      }

      void setValue(Key key, T _t){
          map[key] = _t;
      }

      bool contains(const Key &key){
          sm++;
          QMap<Key, T> _map = map;
          sm--;
          return _map.contains( key );
      }

      QList<Key> keys(){
          sm++;
          QMap<Key, T> _map = map;
          sm--;
          return _map.keys();
      }
      QList<T> values(){
          sm++;
          QMap<Key, T> _map = map;
          sm--;
          return _map.values();
      }


      QMap<Key, T> &getObj(){
          return map;
      }
      inline void operator++ (int){
          sm++;
      }
      inline void operator-- (int){
          sm--;
      }

      size_t size(){
          sm++;
          size_t sz=map.size();
          sm--;
          return sz;
      }

private:

      QMap<Key, T> map;
      QMySemaphore sm;
};

/*template <typename ... types>
struct TPlugsCB_PTR : TCB_PTR<CPluging, types ...>{
    typedef SUniPtr<easyT<CPluging, types ...>> TeasyPTR;

    TPlugsCB_PTR() : sm(1){}

    void NewCB( uint plugID, TeasyPTR ptr ){
        sm++;
        cbPair[plugID] = ptr;
        sm--;
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
    private:
    QMap<int, TeasyPTR> cbPair;
    QMySemaphore sm;
};*/

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

#endif 

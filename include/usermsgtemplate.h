#ifndef TCPS_SCB_H
#define TCPS_SCB_H
#include <QThread>
#include <vector>
#include <QSemaphore>
#include <stdint.h>
#include <QVariant>
#include <QMap>
#include <tuple>

#include <QSharedPointer>
#include <deque>


#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
# define UNUSED(x) /*@unused@*/ x
#else
# define UNUSED(x) x
#endif


#ifndef _SUniPtr
#define _SUniPtr
template < class _class>
struct SUniPtr : public QSharedPointer<_class>{
  typedef QSharedPointer<_class> _uniPnt;
  /*static void doDeletePtr(void *ptr){
      qDebug("DELTEE");
  }*/  
  _class* operator = (_class *ptr){
      //_uniPnt::operator =(_uniPnt( ptr, &SUniPtr::doDeletePtr ));
      _uniPnt::operator =(_uniPnt( ptr ));
      return this->data();
  }
  SUniPtr(){}
  SUniPtr(_class *ptr) : _uniPnt(ptr){}  
};


#endif

#define _DEFPTR( _type, _ptrtype ) typedef SUniPtr<_type> _ptrtype;

class QMySemaphore : public QSemaphore{
public:
  QMySemaphore( int val ) : QSemaphore( val ){
  }
  void operator ++( int ){
	this->acquire();
  };
  void operator --( int ){
	this->release();
  };
};

#ifndef BYTE
typedef unsigned char BYTE;
#endif
template < typename ... Types >
struct _MSGS{
    _MSGS(){}
    _MSGS( Types ... args ){
        setArgs( args ... );
    }

    void setArgs( Types ... args ){
        int nArgsCount = sizeof ... (args);
        QVariant vars[ sizeof ... (args) ] = {args ...};
       //Types vars[ sizeof ... (args) ] = {args ...};

        for ( int i = 0; i < nArgsCount; ++i){
            variant.push_back( *(vars + i) );
        }
    }
    std::vector<QVariant> variant;
};


/*****************************************/
template< std::size_t... Ns >
struct indices {
    typedef indices< Ns..., sizeof...( Ns ) > next;
};

template< std::size_t N >
struct make_indices {
    typedef typename make_indices< N - 1 >::type::next type;
};

template<>
struct make_indices< 0 > {
    typedef indices<> type;
};
/*****************************************/

/*#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;*/

template < typename ... Type>
class CPostEventsVariadic : public QThread{
public:
    CPostEventsVariadic() : sm(1), idle_sm(1), pause_sm(1), in_sm(1){
        m_RunFinished = false;
        vecMSGS.clear();
        bRun = true;
        isPause = false;
        sm++;
        start();
    }
    virtual ~CPostEventsVariadic(){
        //Resume();
        bRun = false;
        if (sm.available() == 0)
        sm--;

        while(!m_RunFinished){
            idle_sm++;
            idle_sm--;
        }
        //qDebug("~CPostEvents() ok");
    }
    void die(){
       // Resume();
        if (this->isRunning()){
          bRun = false;
          if (sm.available() == 0)
          sm--;

          while(!m_RunFinished){
              idle_sm++;
              idle_sm--;
          }
        }
    }

    bool IsEmpty() { return (vecMSGS.size() == 0) ? true : false; }

    inline void AddPostEvent( Type ... args ){
        in_sm++;
        if (bRun){
         std::tuple<Type ...> vt = std::make_tuple(args ...);

         if (vecMSGS.size() > 100){
             qDebug("Fault. Buffer overload. skipping..");
             in_sm--;
             sm--;
             return;
         }
         vecMSGS.push_back( vt );
        }
        in_sm--;
        sm--;
    }

    void BreakQueue(){
      //Resume();

      in_sm++;
      idle_sm++;
      vecMSGS.clear();
      idle_sm--;
      in_sm--;
    }

    void clearQueue(){
      in_sm++;
      vecMSGS.clear();
      in_sm--;
    }

    std::deque<std::tuple<Type ...>> &lockQueue(){
      in_sm++;
      return vecMSGS;
    }

    void unlockQueue(){
      in_sm--;
    }

    template<size_t... Is>
    void call_helper(const std::tuple<Type ...>& _args, indices<Is...>)
    {
        DoIT(  std::get<Is>(_args) ... ); // expand the indices pack
    }

    template<std::size_t Arity>
    void call(const std::tuple<Type ...>& args)
    {
        call_helper(args, typename make_indices<Arity>::type());
    }

    virtual void run(){
        threadID = pthread_self();

        while ( bRun ){
            if ((vecMSGS.size() == 0)&&bRun) sm++;

            ///Do somthing
            idle_sm++;
            if ((vecMSGS.size()!= 0)&&bRun){
              in_sm++;
              std::tuple<Type ...> vararg = vecMSGS.front();
              vecMSGS.pop_front();
              in_sm--;

              call<sizeof ... (Type)>(vararg);
            }
            idle_sm--;
        }
        qDebug("thread cycle end.");
        m_RunFinished = true;
    }

    pthread_t threadID;
    inline void WaitPause() { if (isPause){pause_sm++; pause_sm--;} }
    inline void Resume() { if (isPause) { isPause = false; pause_sm--;} }
    inline void Pause()  { if(!isPause) { pause_sm++; isPause = true; } }
    inline bool IsIdle() { return (idle_sm.available() && (vecMSGS.size() == 0)) ? true : false; }
    inline bool GetLiveStatus(){ return bRun; } ///1 если поток не завершается. Используется для закольцовки.
    inline int  GetQueueSize(){
      in_sm++;
      int count = vecMSGS.size();
      in_sm--;      
      return count;
    }
private:
    volatile bool isPause;
    std::deque<std::tuple<Type ...>> vecMSGS;
    virtual void DoIT( Type ... ){}    
    volatile bool bRun;
    bool m_RunFinished;
    QMySemaphore  sm,///синхронизация обработки сообщений
             idle_sm,
            pause_sm,
               in_sm;	///синхронизация обработки вектора
};

template < class Class, typename ReturnType, typename ... Type>
        class SingularCallBackVariadic : public CPostEventsVariadic< Type ... >{
            public:
                typedef ReturnType (Class::*Method)(Type ...);

                SingularCallBackVariadic(Class* _class_instance, Method _method){
                  class_instance = _class_instance;
                  method         = _method;
                }

                virtual ~SingularCallBackVariadic(){
                }

                ReturnType operator()(Type ... args){
                  return (class_instance->*method)(args ...);
                }

                void execute(Type ... args)
                {
                  operator()(args ...);
                }

            private:
                inline void DoIT( Type ... args ){
                    operator()(args ...);
                }

                Class*  class_instance;
                Method  method;
        };

///CreateCallBackPointer
///_ptr   - указатель на UniPtr
///_class - _typename, после _DEFTMP
///_obj   - указатель на объект
///_func  - указатель на функцию в классе _obj
#define _CREATE_CBPTR( _ptr, _class, _obj, _func) _ptr = new _class( _obj, _func )
#define _CREATE_CBPTR2( _ptr, _obj, _func) _ptr = new CPluging( _obj, _func )

///DefineTemplate
///_class    - класс получатель
///_typename - новый 'сингуляр' тип
#define _DEFTMP( _class, _typename) \
class _class; \
typedef SingularCallBack < _class, void, uint, BYTE*, uint, uint > _typename;

#define _deftmp( _class, _typename, t ... ) \
class _class; \
typedef SingularCallBackVariadic < _class, void, t > _typename;

template < class myClass, typename ... types >
class easyT{
public:
    typedef SingularCallBackVariadic < myClass, void, types ... > AT;
    typedef void (myClass::*Method)(types ...);

    easyT(){}
    easyT( Method method, myClass *pObj ){
        _CREATE_CBPTR(ptrT, AT, pObj, method );
    }
    void AddPostEvent( types ... args ){ ptrT->AddPostEvent( args ... ); }
    void Execute( types ... args ){ ptrT->execute( args ... ); }
    AT* getObj() { return ptrT.data(); }
private:
    typedef SUniPtr<AT> AT_PTR;
    AT_PTR ptrT;
};

#include <QEvent>

#define defType( guiType, idVal ) const QEvent::Type guiType = static_cast<QEvent::Type>(QEvent::User + idVal)

template <typename ... types>
struct TCustomEvent : public QEvent{
    public:
        TCustomEvent( const QEvent::Type guiType, types ... _args ) : QEvent( guiType ){
            args = _MSGS <types ...>( _args ... );
        }

        _MSGS <types ...> args;
};

#endif





#ifndef CAE_H
#define CAE_H

#include <QObject>
#include <QMap>
#include <QVector>
#include "../include/pluging.h"

struct connectInfo{
    connectInfo(){
        pSrcObj = 0;
        pDstObj = 0;
        memset(signal, 0, 512);
        memset(slot, 0, 512);
    }

    connectInfo(QObject *_pSrcObj, QObject *_pDstObj,const char _signal[512],const char _slot[512]){
        pSrcObj = _pSrcObj;
        pDstObj = _pDstObj;
        memset(signal, 0, 512);
        memset(slot, 0, 512);
        strcpy( signal, _signal );
        strcpy( slot, _slot );

    }

    QObject *pSrcObj;
    QObject *pDstObj;

    char signal[512];
    char slot[512];
};

class CaE : QObject{
    Q_OBJECT
public:
    //CaE() : /*sm(1)*/{}
    bool ConnectByPlugID( int plugID ){
        //sm++;        
        for (QVector< QMap<int, connectInfo> >::iterator iter = VECmapConn.begin(); iter != VECmapConn.end(); ++iter)
        if (iter->contains(plugID)){
            connect( iter->value(plugID).pSrcObj, iter->value(plugID).signal, iter->value(plugID).pDstObj, iter->value(plugID).slot );
            //////sm--;
            return true;
        }
        //sm--;
        return false;
    }
    void DisconnectByPlugID( int plugID ){
        //sm++;
        for (QVector< QMap<int, connectInfo> >::iterator iter = VECmapConn.begin(); iter != VECmapConn.end(); ++iter)
            if (iter->contains(plugID))
                disconnect( iter->value(plugID).pSrcObj, iter->value(plugID).signal, iter->value(plugID).pDstObj, iter->value(plugID).slot );
        //sm--;
    }
    void DropByPlugID( int plugID ){
        ///// sm++;
        for (QVector< QMap<int, connectInfo> >::iterator iter = VECmapConn.begin(); iter != VECmapConn.end();)
            if (iter->contains(plugID)) VECmapConn.erase( iter ); else ++iter;
        //sm--;

    }
    void AddByPlugID( QObject *pSrcObj, QObject *pDstObj,const char signal[128],const char slot[128], int plugID ){
        //sm++;
        QMap<int, connectInfo> mapConn;
        mapConn[plugID] = connectInfo(pSrcObj, pDstObj, signal, slot);
        VECmapConn.push_back( mapConn );
        //sm--;
    }
private:
    QVector< QMap<int, connectInfo> > VECmapConn;
    //QMySemaphore sm;
};

#endif // CAE_H

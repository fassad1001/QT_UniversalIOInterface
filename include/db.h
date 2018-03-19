#ifndef DB_H
#define DB_H

#include <QDebug>
//#include <QSqlDatabase>
//#include <QSqlQuery>
#include <QApplication>
#include <windows.h>

//static uint db_counter = 0;

//struct ParamMainMenu{
//    QString name;
//    int position;
//    int command;
//};

struct ParamSerialPort{
    QString port;
    int rate;
    int dbits;
    int sbits;
    int parity;
};

//class CPlugList;
//class dbsqlite{
//    friend class CPlugList;
//    dbsqlite(){
//        Init();
//    }

//    dbsqlite( QString _query ){
//        Init();
//        result = query.exec( _query );
//    }
//    ~dbsqlite(){
//        query.finish();
//        query = QSqlQuery();
//        mdb.close();
//        mdb = QSqlDatabase();
//        QSqlDatabase::removeDatabase(conname);
//    }

//public:

//    void beginTransaction(){ query.exec("BEGIN IMMEDIATE TRANSACTION;"); }
//    void endTransaction(){ query.exec("COMMIT TRANSACTION;"); }

//    void writeQuery( QString _query ){
//        query.exec("BEGIN IMMEDIATE TRANSACTION;");
//        result = query.exec( _query );
//        query.exec("COMMIT TRANSACTION;");
//    }

//    QSqlQuery* operator -> (void){
//        return &query;
//    }

//    QSqlDatabase GetDatabase(){ return mdb; }

//    bool AllParamMainMenu(QVector<ParamMainMenu> &params)
//    {
//        QString queryStr = QString("SELECT * FROM MainMenu ORDER BY position;");
////        if(!query.exec(queryStr)) return false;

//        ParamMainMenu param;
////        while(query.next()){
////            param.name     = query.value("name").toString();
////            param.position = 7 + query.value("position").toInt();
////            param.command  = query.value("command").toInt();
////            params.push_back(param);
////        }

//        return true;
//    }

//    bool InitParamMainMenu(QVector<ParamMainMenu> &params){
//        return InitParamMainMenuExt(params);
//    }

//    bool InitParamMainMenuExt(QVector<ParamMainMenu> &params, int PlugID = -1)
//    {
//        extern int __PLUGID_M;
//        QString queryStr = QString("SELECT * FROM MainMenu WHERE plugid='%1' ORDER BY position;").arg(PlugID == -1 ? __PLUGID_M : PlugID);
////        if(!query.exec(queryStr)) return false;

//        ParamMainMenu param;
////        while(query.next()){
////            param.name     = query.value("name").toString();
////            param.position = 7 + query.value("position").toInt();
////            param.command  = query.value("command").toInt();
////            params.push_back(param);
////        }

//        return true;
//    }

//    bool InitParamSerialPort(ParamSerialPort &param){
//        return InitParamSerialPortExt(param);
//    }

//    bool InitParamSerialPortExt(ParamSerialPort &param, int PlugID = -1)
//    {
//        extern int __PLUGID_M;
//        QString queryStr = QString("SELECT * FROM com JOIN plugid on plugid.id=%1 and plugid.devid=com.devid").arg(PlugID == -1 ? __PLUGID_M : PlugID);
////        if(!query.exec(queryStr)) return false;

//        param.port   = "";
//        param.rate   = 0;
//        param.dbits  = 0;
//        param.sbits  = 0;
//        param.parity = 0;

////        while(query.next()){
////            param.port   = query.value("port").toString();
////            param.rate   = ConvertRate(query.value("rate").toString());
////            param.dbits  = ConvertDBits(query.value("dbits").toString());
////            param.sbits  = ConvertSBits(query.value("sbits").toString());
////            param.parity = ConvertParity(query.value("parity").toString());
////        }

//        return true;
//    }

//    int ConvertRate(QString value)
//    {
//        bool ok = false;
//        int int_value = value.toInt(&ok);
//        if (!ok) return CBR_9600;

//        if (int_value != CBR_1200 && int_value != CBR_2400
//                && int_value != CBR_4800 && int_value != CBR_9600
//                && int_value != CBR_14400 && int_value != CBR_19200
//                && int_value != CBR_38400 && int_value != CBR_57600
//                && int_value != CBR_115200) {
//            return CBR_9600;
//        }

//        return int_value;
//    }

//    int ConvertSBits(QString value)
//    {
//        bool ok = false;
//        float f_value = value.toFloat(&ok);
//        if (!ok) return ONESTOPBIT;

//        if (f_value == 1) {
//            return ONESTOPBIT;
//        } else if (f_value == 1.5) {
//            return ONE5STOPBITS;
//        } else if (f_value == 2) {
//            return TWOSTOPBITS;
//        }

//        return ONESTOPBIT;
//    }

//    int ConvertDBits(QString value)
//    {
//        bool ok = false;
//        int int_value = value.toInt(&ok);
//        if (!ok) return 8;

//        if (int_value < 5 && int_value > 8) {
//            return 8;
//        }

//        return int_value;
//    }

//    int ConvertParity(QString value)
//    {
//        if (value == "n") {
//            return NOPARITY;
//        } else if (value == "o") {
//            return ODDPARITY;
//        } else if (value == "e") {
//            return EVENPARITY;
//        } else if (value == "m") {
//            return MARKPARITY;
//        } else if (value == "s") {
//            return SPACEPARITY;
//        }

//        return NOPARITY;
//    }

////    QSqlQuery query;
//    bool result;
//private:
////    QSqlDatabase mdb;
//    QString conname;
//    void Init(){
//        conname = QString("conn%1%2").arg(++db_counter).arg((qlonglong)this);
//        mdb = QSqlDatabase::addDatabase("QSQLITE", conname);
//        mdb.setConnectOptions("QSQLITE_BUSY_TIMEOUT=5;QSQLITE_ENABLE_SHARED_CACHE=1");
//        mdb.setDatabaseName("settings.s3db");
//        result = mdb.open();

//        query = QSqlQuery(mdb);
//    }
//};

#endif // DB_H


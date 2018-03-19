#ifndef CSERIAL_H
#define CSERIAL_H

#include "windows.h"
#include <QString>

__attribute__((unused))
static BOOL SetRTS (HANDLE hCom, bool v)
{
    BOOL Success;

    switch (v) {
    case 1 :
        Success = EscapeCommFunction(hCom, SETRTS);
        break;

    case 0 :
        Success = EscapeCommFunction(hCom, CLRRTS);
        break;

    default :
        Success = 0;
        break;
    }

    return Success;
}

__attribute__((unused))
static bool GetCTS (HANDLE hCom)
{
    DWORD Modem;
    GetCommModemStatus(hCom, &Modem);

    return (Modem & MS_CTS_ON) ? true : false;
}

__attribute__((unused))
static std::string GetLastErrorStdStr()
{
  DWORD error = GetLastError();
  if (error)
  {
    LPVOID lpMsgBuf;
    DWORD bufLen = FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        error,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );
    if (bufLen)
    {
      LPCSTR lpMsgStr = (LPCSTR)lpMsgBuf;
      std::string result(lpMsgStr, lpMsgStr+bufLen);

      LocalFree(lpMsgBuf);

      return result;
    }
  }
  return std::string();
}


class CSerial
{
public:
    CSerial();    
    CSerial( QString _SerialName );
    ~CSerial(){ close(); }
    bool open( char _SerialName[16], long _IO );
    bool open( long _IO );

    bool init(DWORD BaudRate, BYTE ByteSize, BYTE StopBits, BYTE Parity );
    bool init();
    void close();

    bool setBaudRate( DWORD );
    bool setStopBits( BYTE );
    bool setParity( BYTE );
    bool setFlowControl( DWORD );
    bool setDataBits( BYTE );
    bool setRequestToSend( bool, int timeout = 50 );
    bool waitForReadyRead( int );
    bool waitForBytesWritten( int );
    void flush(){ FlushFileBuffers(hSerial); }

    void setReadTimeouts(DWORD readIntervalTimeout,
                         DWORD readTotalTimeoutConstant,
                         DWORD readTotalTimeoutMultiplier);


    int  write( QByteArray  ba );

    inline bool isOpen() { return IsOpen; }
    void setPortName( QString portName ){ strcpy(SerialName, portName.toStdString().c_str() );}

    QByteArray readAll();

private:
    HANDLE hSerial;
    DCB dcbSerialParams;
    COMMTIMEOUTS timeouts;
    char SerialName[16];
    bool IsOpen;
};

#endif // CSERIAL_H

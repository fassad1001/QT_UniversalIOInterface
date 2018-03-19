#include "cserial.h"

CSerial::CSerial()
{
    memset( &dcbSerialParams, 0, sizeof(DCB) );
    memset( &timeouts, 0, sizeof(COMMTIMEOUTS) );

    dcbSerialParams.DCBlength=sizeof(dcbSerialParams);

    dcbSerialParams.BaudRate=CBR_9600;
    dcbSerialParams.ByteSize=DATABITS_8;
    dcbSerialParams.StopBits=ONESTOPBIT;
    dcbSerialParams.Parity=NOPARITY;
    dcbSerialParams.fParity = true;

    timeouts.ReadIntervalTimeout=10;
    timeouts.ReadTotalTimeoutConstant=50;
    timeouts.ReadTotalTimeoutMultiplier=10;

    timeouts.WriteTotalTimeoutConstant=50;
    timeouts.WriteTotalTimeoutMultiplier=10;

    hSerial = INVALID_HANDLE_VALUE;
    IsOpen = false;
    memset(SerialName, 0, 16);
}
CSerial::CSerial( QString _SerialName ){
    memset(SerialName, 0, 16);
    strcpy(SerialName, _SerialName.toStdString().c_str());
    SerialName[_SerialName.size()] = '\0';
    memset( &dcbSerialParams, 0, sizeof(DCB) );
    memset( &timeouts, 0, sizeof(COMMTIMEOUTS) );
    dcbSerialParams.DCBlength=sizeof(dcbSerialParams);

    dcbSerialParams.BaudRate=CBR_9600;
    dcbSerialParams.ByteSize=DATABITS_8;
    dcbSerialParams.StopBits=ONESTOPBIT;
    dcbSerialParams.Parity=NOPARITY;
    dcbSerialParams.fParity = true;
    dcbSerialParams.fRtsControl = true;

    timeouts.ReadIntervalTimeout=0;
    timeouts.ReadTotalTimeoutConstant=50;
    timeouts.ReadTotalTimeoutMultiplier=0;

    timeouts.WriteTotalTimeoutConstant=50;
    timeouts.WriteTotalTimeoutMultiplier=0;

    hSerial = INVALID_HANDLE_VALUE;
    IsOpen = false;
}

bool CSerial::open( long _IO ){
    return open(SerialName, _IO);
}

bool CSerial::open(char _SerialName[16], long _IO ){    
    char com[16] = {0};
    sprintf(com, "\\\\.\\%s", _SerialName);
    hSerial = CreateFileA(com,
    _IO,
    0,
    0,
    OPEN_EXISTING,
    FILE_ATTRIBUTE_NORMAL,
    0);

    if(hSerial==INVALID_HANDLE_VALUE){
    if(GetLastError()==ERROR_FILE_NOT_FOUND){
    //serial port does not exist. Inform user.
        qDebug("serial port does not exist");
        return false;
    }
    //some other error occurred. Inform user.
        qDebug("error while opening com port");
        return false;
    }
    qDebug("serial port %s opens OK", com);

    init();

    IsOpen = true;
    return true;
}

bool CSerial::init(){
    DCB m_dcbSerialParamsCur;
    memset( &m_dcbSerialParamsCur, 0, sizeof(DCB) );
    m_dcbSerialParamsCur.DCBlength = sizeof(DCB);


    if (!GetCommState(hSerial, &m_dcbSerialParamsCur)) {
    //error getting state
    }

    m_dcbSerialParamsCur.BaudRate = dcbSerialParams.BaudRate;
    m_dcbSerialParamsCur.ByteSize = dcbSerialParams.ByteSize;
    m_dcbSerialParamsCur.StopBits = dcbSerialParams.StopBits;
    m_dcbSerialParamsCur.Parity   = dcbSerialParams.Parity;
    m_dcbSerialParamsCur.fParity  = dcbSerialParams.fParity;
    m_dcbSerialParamsCur.fRtsControl = dcbSerialParams.fRtsControl;

    if(!SetCommState(hSerial, &m_dcbSerialParamsCur)){
    //error setting serial port state
        qDebug("error setting serial port state");
        qDebug ("GetCommState failed with error %s.\n", GetLastErrorStdStr().c_str());
        return false;
    }

    if(!SetCommTimeouts(hSerial, &timeouts)){
    //error occureed. Inform user
        qDebug("error occureed.");
        qDebug ("GetCommState failed with error %s.\n", GetLastErrorStdStr().c_str());
        return false;
    }
    return true;
}

bool CSerial::init( DWORD BaudRate, BYTE ByteSize, BYTE StopBits, BYTE Parity ){

    dcbSerialParams.DCBlength=sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
    //error getting state
    }
    dcbSerialParams.BaudRate=BaudRate;
    dcbSerialParams.ByteSize=ByteSize;
    dcbSerialParams.StopBits=StopBits;
    dcbSerialParams.Parity=Parity;

    if(!SetCommState(hSerial, &dcbSerialParams)){
    //error setting serial port state
        qDebug("error setting serial port state");
        qDebug ("GetCommState failed with error %d.\n", (int)GetLastError());
        return false;
    }

    if(!SetCommTimeouts(hSerial, &timeouts)){
    //error occureed. Inform user
        qDebug("error occureed.");
        qDebug ("GetCommState failed with error %d.\n", (int)GetLastError());
        return false;
    }

    return true;
}

void CSerial::close(){
    if( hSerial!=0 && hSerial!=INVALID_HANDLE_VALUE){
       CloseHandle( hSerial );
       hSerial = 0;
       qDebug("Close serial");
       IsOpen = false;
    }
}

int CSerial::write( QByteArray ba ){
    if( hSerial==0 || hSerial==INVALID_HANDLE_VALUE) return -1;

    //FlushFileBuffers(hSerial);
    DWORD dwBytesWrite = 0;
    if(!WriteFile(hSerial, ba.data(), ba.size(), &dwBytesWrite, NULL)){
    //error occurred. Report to user.
    }

    return dwBytesWrite;
}

QByteArray CSerial::readAll(){
    QByteArray ba;

    if( hSerial==0 || hSerial==INVALID_HANDLE_VALUE)
    return ba;

    //FlushFileBuffers(hSerial);

    char szBuff[32] = {0};
    DWORD dwBytesRead = 0;

    do{
    if(!ReadFile(hSerial, szBuff, 32, &dwBytesRead, NULL)){
    //error occurred. Report to user.
        qDebug("error on read");
        ba.clear();
        return ba;
    }
        if (dwBytesRead > 0){
            //for (DWORD i = 0; i < dwBytesRead; i++){
            //ba.push_back(szBuff);
            ba.append( szBuff, dwBytesRead );
            //}
        }
    }while(dwBytesRead > 0);

    return ba;
}


bool CSerial::setBaudRate( DWORD BaudRate ){
    dcbSerialParams.BaudRate=BaudRate;
    return init();
}

bool CSerial::setStopBits( BYTE StopBits ){
    dcbSerialParams.StopBits=StopBits;
    return init();
}

bool CSerial::setParity( BYTE Parity ){
    dcbSerialParams.Parity=Parity;
    return init();
}

bool CSerial::setFlowControl( DWORD ){
    return init();
}

bool CSerial::setDataBits( BYTE ByteSize ){
    dcbSerialParams.ByteSize=ByteSize;
    return init();
}

bool CSerial::setRequestToSend( bool f, int timeout ){
    //dcbSerialParams.fRtsControl = f ? RTS_CONTROL_ENABLE : RTS_CONTROL_ENABLE | RTS_CONTROL_TOGGLE;
    //init();
    SetRTS( hSerial, f );
    Sleep(timeout);

    if (f){
        if ( GetCTS( hSerial ) ){
             return true;
        }else{
            qDebug("CTS FAIL");
            return false;
        }
    }

    return true;
}

bool CSerial::waitForReadyRead( int timeout ){
    timeouts.ReadTotalTimeoutConstant = timeout;
    return init();
}

bool CSerial::waitForBytesWritten( int timeout ){
    timeouts.WriteTotalTimeoutConstant = timeout;
    return init();
}

void CSerial::setReadTimeouts(DWORD readIntervalTimeout, DWORD readTotalTimeoutConstant, DWORD readTotalTimeoutMultiplier)
{
    timeouts.ReadIntervalTimeout = readIntervalTimeout;
    timeouts.ReadTotalTimeoutConstant = readTotalTimeoutConstant;
    timeouts.ReadTotalTimeoutMultiplier = readTotalTimeoutMultiplier;
}

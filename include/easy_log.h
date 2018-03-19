#ifndef EASY_LOG_H
#define EASY_LOG_H

#define LOGVER 0x02

#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>
#include <time.h>
#include <QSemaphore>
#include <stdint.h>

static inline uint64_t rdtsc() {
uint64_t d;
__asm__ __volatile__ ("rdtsc" : "=A" (d) );
return d;
}

#define BILLION  1000000000L

static struct STimeCounter{
  STimeCounter(){
     b_run = false;
  };
  
  struct timespec t_start, t_stop;
  
  inline void start(){
    if (b_run){
      return;
    }else
      b_run = true;
    
    clock_gettime(CLOCK_REALTIME, &t_start);    
  }
  
  inline double stop(){
    if (b_run){
      b_run = false;      
    }else
      return 0.0;      
    
    clock_gettime(CLOCK_REALTIME, &t_stop);
    return ( t_stop.tv_sec - t_start.tv_sec ) + (double)( t_stop.tv_nsec - t_start.tv_nsec ) / (double)BILLION;
  }
private:
  bool b_run;
}m_tc;

struct SLOG{
    SLOG(){}
	SLOG(const char *fname, const char *msg ){
		FILE *pf = NULL;		
		
		pf = fopen( fname, "a+" );
		if ( pf ){
            char chTime[50];
            //struct timeval tv;
            //struct tm today;
            //time_t ltime;

            //gettimeofday(&tv, NULL);
            //time_t tvsec = tv.tv_sec;
            //tm* timeinfo = localtime_s(&tvsec);

            //localtime_s( &today, &ltime );

            time_t rawtime;
            time(&rawtime);
            tm* timeinfo = localtime (&rawtime);
            strftime( chTime, 50, "%d%m%Y %H:%M:%S", timeinfo );

			fprintf( pf, "<%s> %s\n", chTime, msg );
			qDebug("<%s> %s", chTime, msg);
			fclose( pf );
		}
    }
	SLOG( char* pczFILE, char* pczFunction, int LINE, const char *fname, const char *msg ){
		FILE *pf = NULL;

		char chTime[30];
        //struct timeval tv;struct tm today;
        //time_t ltime;

        //gettimeofday(&tv, NULL);
        //time_t tvsec = tv.tv_sec;

        //localtime_s( &today, &ltime );

        time_t rawtime;
        time(&rawtime);
        tm* timeinfo = localtime (&rawtime);

        strftime( chTime, 30, "%d/%m/%Y  %H:%M:%S", timeinfo );

		pf = fopen( fname, "a+" );
		if ( pf ){
			fprintf( pf, "[%s %s (%s:%d)] %s\n", chTime, pczFILE, pczFunction, LINE, msg );
			fclose( pf );			
		}
		qDebug("[%s %s (%s:%d)] %s", chTime, pczFILE,pczFunction, LINE, msg);
    }
};

static struct LOG{
	LOG() : m_Sem(1) {
		chFILE = NULL;
		chFunction = NULL;
		iLINE = 0;
    }

	inline void lock(){
		//m_Sem.acquire();
    }
	inline void operator++(int ){
		//m_Sem.acquire();
    }
	inline void operator--(int){
		//m_Sem.release();
    }

	inline void out(const char *fname, const char *msg, ...){
		const int BUFSIZE = 4096;
		char pczComBuf[BUFSIZE]="";
	
		va_list va;
		va_start(va,msg);
		vsnprintf(pczComBuf,BUFSIZE-1,msg,va), pczComBuf[BUFSIZE-1]=0;
		va_end(va);
		
		if (chFILE != NULL){
			SLOG( chFILE, chFunction, iLINE, fname, pczComBuf );
		}else
			SLOG(fname, pczComBuf);
		chFILE = NULL;
	}
	inline void outex( const char* pczFILE, const char* pczFunction, const int LINE ){
		chFILE = (char *)pczFILE;
		chFunction = (char *)pczFunction;
		iLINE = (int)LINE;
	}
	inline void unlock(){
		//m_Sem.release();
    }
private:
	QSemaphore m_Sem;
	char* chFILE;
	char* chFunction;
	int   iLINE;
}m_log;

#define m_logout  m_log.outex(__FILE__,__FUNCTION__, __LINE__), m_log.out

#define tc_begin m_tc.start()
#define tc_end(S)   qDebug("%s tc_time = %.8f", S, m_tc.stop())

#endif

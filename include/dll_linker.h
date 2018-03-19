//#include "../src/easy_log.h"
#include "dlfcn.h"
#include <iostream>
#include <QSemaphore>
#include <stdint.h>
//#include "rhead.h"

#ifndef BYTE
typedef unsigned char BYTE;
#endif

#ifndef CDLLLINKER_H
#define CDLLLINKER_H

template < class Class >
class CDllLink{        
        public:
                enum {DEFAULT = 0, SELF_CREATE_AND_DESTROY = 1};
        CDllLink() : sm(1){}
                CDllLink(const char* dllname, const char* create_func, const char* destroy_func, QObject *parent, unsigned char flag = DEFAULT) : sm(1) {
                        FLAG = flag;
                        pObj = NULL;
			
						
            handle = dlopen( dllname, RTLD_NOW|RTLD_LOCAL);

			
			if (handle){
                create  = (Class* (*)(QObject*))dlsym(handle, create_func);
                destroy = (void (*)(Class*))dlsym(handle, destroy_func);                
			}else{
				
				qDebug("%s\n", dlerror());

				create = NULL;
                destroy= NULL;                
			}

                        if (FLAG == SELF_CREATE_AND_DESTROY)
                            create_inner_object(parent);
        }
	
                ~CDllLink(){
                        if (pObj)
                        if (FLAG == SELF_CREATE_AND_DESTROY)
                            destroy_object((Class*)pObj);
			pObj = NULL;

			if (handle)
				if ( dlclose(handle) != 0 )
					 qDebug("%s\n", dlerror());
		}

        Class *create_object(QObject* parent){
			if (create){
                return (Class*)create(parent);
			}else
				return NULL;
        }

                void create_inner_object(QObject *parent){
                    if (create){
                            pObj = (void*)create(parent);
                    }else{
                            pObj = NULL;
                            return;
                    }
                }

                Class* GetObj(){
                    return (Class*)pObj;
                }
		
		void destroy_object( Class* object ){
			if (destroy)
				destroy(object);
                        //pObj = NULL;
        }

                void* GetHandle(){ return handle; }
	private:
		void* handle;		
        void *pObj;

        Class* (*create)(QObject*);
        void (*destroy)(Class*);
		
		QSemaphore sm;

        unsigned char FLAG;
		
};

#endif

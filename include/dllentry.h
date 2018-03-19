#ifndef CDP_H
#define CDP_H

#include "../../defines/commandlist.h"
//#include <qstring.h>
//#include <types.h>

class CPrimaryDataProcessing
{
public:

	void CallMessage(UINT64 type, BYTE *data, UINT64 data_size, UINT64 id){};
	CPrimaryDataProcessing();
	~CPrimaryDataProcessing();
};

#endif

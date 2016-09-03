/*
 * IVTEntry.h
 *
 *  Created on: Aug 27, 2016
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_
#include "KernelEv.h"

typedef void interrupt(*pInterrupt)(...);
typedef unsigned char IVTNo;


class IVTEntry{

public:
	KernelEv *myKernelEv;
	IVTEntry(IVTNo no, pInterrupt newRoutine);
	~IVTEntry();
	void callOldR();
	void signal();

private:

pInterrupt oldR;
int ivtNo;
};



#endif /* IVTENTRY_H_ */

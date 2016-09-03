/*
 * IVTEntry.cpp
 *
 *  Created on: Aug 27, 2016
 *      Author: OS1
 */

#include "IVTEntry.h"
#include "Nucleus.h"
#include "Lock.h"
#include <dos.h>

IVTEntry::IVTEntry(IVTNo no, pInterrupt newRoutine){
Nucleus::IVTTable[no]=this;
ivtNo=no;
#ifndef BCC_BLOCK_IGNORE
oldR= getvect(no);
setvect(no, newRoutine);
#endif
}

IVTEntry::~IVTEntry(){
	Lock();
#ifndef BCC_BLOCK_IGNORE
	setvect(ivtNo, oldR);
#endif
	Unlock();

}

void IVTEntry::callOldR(){
	Lock();
	(*oldR)();
	Unlock();
}

void IVTEntry::signal(){
	Lock();
	myKernelEv->signal();
	Unlock();

}



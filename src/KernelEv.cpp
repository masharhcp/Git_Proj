/*
 * KernelEv.cpp
 *
 *  Created on: Aug 26, 2016
 *      Author: OS1
 */
#include "KernelEv.h"
#include "Lock.h"
#include "Nucleus.h"
#include "Schedule.h"

	KernelEv::KernelEv(IVTNo ivtN){
		Lock();
		ivtNo=ivtN;
		maker=(PCB*)Nucleus::running;
		Nucleus::IVTTable[ivtNo]->myKernelEv=this;
		value=0;
		blocked=0;
		Unlock();
	}

	KernelEv::~KernelEv(){
		Lock();
		Nucleus::IVTTable[ivtNo]->myKernelEv=0;
		maker=0;
		blocked=0;
		Unlock();

	}


    void KernelEv::signal(){
    	Lock();
    	if(maker->state==PCB::BLOCKED && value==0){
    		maker->state=PCB::READY;
    		Scheduler::put(maker);
    	}
    	value=1;
    	Unlock();

    }

   void KernelEv::wait(){
    	Lock();
    	if (Nucleus::running==maker){
    		if (value==0){
    			Nucleus::running->state=PCB::BLOCKED;
    			dispatch();
    	}
    	if (value==1)value=0;


    }
    	Unlock();
   }




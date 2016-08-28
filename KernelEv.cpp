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
		Unlock();
	}

	KernelEv::~KernelEv(){
		Nucleus::IVTTable[ivtNo]->myKernelEv=0;

	}

    void KernelEv::signal(){
    	if(maker==0)value=1;
    	else{
    		maker->state=PCB::READY;
    		if(maker!=Nucleus::idle)
    		Scheduler::put(maker);
    		maker=0;
    	}

    }

    void KernelEv::wait(){
    	if (Nucleus::running==maker){
    		if(value==0){
    			Nucleus::running->state=PCB::BLOCKED;
    			dispatch();
    		}
    		else
    			if (value==1)value=0;

    	}

    }


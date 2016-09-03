/*
 * KernelSem.cpp
 *
 *  Created on: Aug 21, 2016
 *      Author: OS1
 */
#include "KernSem.h"
#include "Nucleus.h"
#include "Lock.h"
#include "Schedule.h"
KernelSem::KernelSem(int val){
	value=val;
	BlockedPCBs=new PCBList();
	Nucleus::sems->Add(this);
}

int KernelSem::wait(Time maxTimeToWait){//povratna vrednost; vidi kad koja i vrati;
	int retValue;
	value--;
	if (value<0)
		block(maxTimeToWait);

	retValue=Nucleus::running->waitVal;
	Nucleus::running->waitVal=1;
	return retValue;
}

void KernelSem::signal(){

	if(value++<0)unblock();

	}

int KernelSem::val(){
	return value;
}

void KernelSem::block(Time time){
	Lock();
	Nucleus::running->state=PCB::BLOCKED;
	Nucleus::running->mySem=this;
	if (time>0)Nucleus::pcbQueue->Add((PCB*)Nucleus::running, time);
	BlockedPCBs->Add((PCB*)Nucleus::running);
	dispatch();
	Unlock();
	}

void KernelSem::unblock(){
	PCB* hel=BlockedPCBs->Get_First();
	if (hel->MaxBlockTime>0){
		Nucleus::pcbQueue->Remove_By_ID(hel->ID);
		hel->MaxBlockTime=-1;
	}
	hel->waitVal=1;
	hel->mySem=0;
	hel->state=PCB::READY;
	BlockedPCBs->Remove_First();
	Scheduler::put(hel);

	}

KernelSem::~KernelSem(){//deblokiraj ih sve pre nego sto obrises semafor

		delete BlockedPCBs;
	}

PCBList* KernelSem::Get_BlockedPCBs(){
	return BlockedPCBs;
}
int KernelSem::Get_Sem_Value(){
	return value;
}

void KernelSem::Dec_Sem_Value(){
	value--;
}

void KernelSem::Inc_Sem_Value(){
	value++;
}

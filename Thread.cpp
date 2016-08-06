#include "Thread.h"
#include "PCB.h"
#include "Nucleus.h"
#include "Lock.h"
#include "iostream.h"
#include "SCHEDULE.H"

Thread::Thread(StackSize stackSize, Time timeSlice){
	Lock();
	myPCB=new PCB(stackSize, timeSlice, this);
	Unlock();
}

Thread::~Thread(){}

void Thread::start(){//proveri da li se vise puta pozvalo za istu nit
	Lock();
	myPCB->state=PCB::READY;
	pcbs.Add(myPCB);
	Scheduler::put(myPCB);
	Unlock();
}


ID Thread::getRunningId(){
	return running->ID;
}

ID Thread::getId(){
	return myPCB->ID;
}

Thread * Thread::getThreadById(ID id){
	PCB *p=pcbs.Get_By_ID(id);
	return p->myThread;
}

void Thread::waitToComplete(){//provera za starting i idle
	Lock();
	if(myPCB->state==PCB::FINISHED){Unlock(); return;}
	if(myPCB==running){Unlock(); return;}
	running->state=PCB::BLOCKED;
	running->BlockedOn=myPCB;
	myPCB->WaitingOnMe->Add(running);
	dispatch();
	Unlock();
}

void dispatch(){
	Lock();
	demand_context_change = 1;
	Timer();
	Unlock();
}



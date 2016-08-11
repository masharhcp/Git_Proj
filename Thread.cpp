#include "Thread.h"
#include "PCB.h"
#include "Nucleus.h"
#include "Lock.h"
#include "iostream.h"
#include "SCHEDULE.H"
#include "IdleT.h"


Thread::Thread(StackSize stackSize, Time timeSlice){
	Lock();
	myPCB=new PCB(stackSize, timeSlice, this);
	Unlock();
}

Thread::~Thread(){}

void Thread::start(){
	Lock();
	myPCB->InitStack();
	myPCB->state=PCB::READY;
	Nucleus::pcbs.Add(myPCB);
	Scheduler::put(myPCB);
	Unlock();
}


ID Thread::getRunningId(){
	return Nucleus::running->ID;
}

ID Thread::getId(){
	return myPCB->ID;
}

Thread * Thread::getThreadById(ID id){
	PCB *p=Nucleus::pcbs.Get_By_ID(id);
	return p->myThread;
}

void Thread::waitToComplete(){//provera za starting i idle
	Lock();
	if(myPCB->state==PCB::FINISHED){Unlock(); return;}
	if(myPCB==(Nucleus::running)){Unlock(); return;}
	Nucleus::running->state=PCB::BLOCKED;
	Nucleus::running->BlockedOn=myPCB;
	myPCB->WaitingOnMe->Add(Nucleus::running);
	dispatch();
	Unlock();
}

void dispatch(){
	Lock();
	Nucleus::demand_context_change = 1;
	Nucleus::Timer();
	Unlock();
}



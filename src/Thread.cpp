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

Thread::~Thread(){
	Lock();
	//waitToComplete();
	delete myPCB;
	Unlock();
}

void Thread::start(){
	Lock();
	myPCB->InitStack();
	myPCB->state=PCB::READY;
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
	PCB *p=Nucleus::pcbList->Get_By_ID(id);
	return p->myThread;
}

void Thread::waitToComplete(){
	Lock();
	if(myPCB->state==PCB::FINISHED){Unlock(); return;} //nit se ne sme blokirati na niti koja je zavrsila sa radom
	if(myPCB==(Nucleus::running)){Unlock(); return;} //ne sme se blokirati na samoj sebi
	if(this==(Nucleus::starting)){Unlock(); return;} //ne sme se blokirati na pocetnoj niti (main) jer se ona mora zavrsiti poslednja
	if(this==(Nucleus::idle)){Unlock(); return;} //ne sme se blokirati na idle niti jer se ona nikad nece zavrsiti
	Nucleus::running->state=PCB::BLOCKED;
	Nucleus::running->BlockedOn=myPCB; //pokazivac na nit na kojoj je blokirana
	myPCB->WaitingOnMe->Add((PCB*)Nucleus::running); //ubacuje se u niz blokiranih na toj niti
	dispatch();
	Unlock();
}

void dispatch(){
	Lock();
	Nucleus::demand_context_change = 1;
	Nucleus::Timer();
	Unlock();
}

//void tick(){}

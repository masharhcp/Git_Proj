#include "IdleT.h"
#include "Nucleus.h"
#include "PCB.h"
#include "Thread.h"
#include "Lock.h"

class Thread;
class PCB;
IdleT::IdleT():Thread(256 ,0){}

void IdleT::run(){
	k=1;
	while (k==1){}
}

void IdleT::start(){
	Lock();
		myPCB->state = PCB::READY;
		myPCB->InitStack();
	Unlock();

}


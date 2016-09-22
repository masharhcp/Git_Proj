#include "PCB.h"
#include "Thread.h"
#include "PCBList.h"
#include "Nucleus.h"
#include <iostream.h>
#include <dos.h>
#include "Lock.h"


unsigned PCB::id=0;
PCB::PCB(unsigned long stackSize, unsigned int timeSlice, Thread *thread){
	sSize=stackSize/sizeof(unsigned);
	tSlice=timeSlice;
	myThread=thread;
	ID=id++;
	state=CREATED;
	MaxBlockTime=-1;
	waitVal=1;
	Nucleus::pcbList->Add(this);
	WaitingOnMe=new PCBList();

}

PCB::~PCB(){
	Lock();
	delete WaitingOnMe;
	Unlock();
}

void PCB::InitStack(){
	Lock();
	stack=new unsigned[sSize];
	#ifndef BCC_BLOCK_IGNORE
							//ukoliko nasa metoda wrapper prima argument njegov offset i segment bi bili na prve dve lokacije steka
	stack[sSize-3]=0x200; //dva prazna mesta zbog callback funkcije; postavljanje PSWI na 1
	stack[sSize-4]=FP_SEG(Wrapper); //postavljanje CS-a koji je jedak segmentu wrappera(Code segment, segment za PC)
	stack[sSize-5]=FP_OFF(Wrapper); //postavljanje IP-a koji je jednak offsetu wrappera(Instruction pointer, offset za PC)
	//ostaviti mesta za registre procesora pri ulasku u interrupt rutinu
	sp = FP_OFF(stack+sSize-14);
	bp = FP_OFF(stack+sSize-14);
	ss = FP_SEG(stack+sSize-14);
	#endif
	Unlock();

}

void PCB::Wrapper(){

	 Nucleus::running->myThread->run();
	 Lock();
	 Nucleus::running->WaitingOnMe->Unblock_All();
	 Nucleus::running->state=PCB::FINISHED;
	 Unlock();
	 dispatch();
}


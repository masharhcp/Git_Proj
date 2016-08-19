#include "PCB.h"
#include "Thread.h"
#include "PCBList.h"
#include "Nucleus.h"
#include <iostream.h>
#include <dos.h>
#include "Lock.h"

unsigned PCB::id=0;
PCB::PCB(unsigned long stackSize, unsigned int timeSlice, Thread *thread){
	sSize=stackSize/2;
	tSlice=timeSlice;
	myThread=thread;
	ID=++id;
	state=CREATED;
	Nucleus::pcbs.Add(this);
	WaitingOnMe=new PCBList();

}

PCB::~PCB(){
	Lock();
	delete WaitingOnMe;
	Unlock();
}

void PCB::InitStack(){
	stack=new unsigned[sSize];
	#ifndef BCC_BLOCK_IGNORE
	//stack[sSize-1]=FP_SEG(myThread);
	//stack[sSize-2]=FP_OFF(myThread); //ukoliko nasa metoda wrapper prima argument tipa Thread
	stack[sSize-1]=0x200; //dva prazna mesta zbog callback funkcije; postavljanje PSWI na 1
	stack[sSize-2]=FP_SEG(Wrapper); //postavljanje CS-a koji je jedak segmentu wrappera(Code segment, segment za PC)
	stack[sSize-3]=FP_OFF(Wrapper); //postavljanje IP-a koji je jednak offsetu wrappera(Instruction pointer, offset za PC)
	//ostaviti mesta za registre procesora pri ulasku u interrupt rutinu
	sp = FP_OFF(stack+sSize-12);
	bp = FP_OFF(stack+sSize-12);
	ss = FP_SEG(stack+sSize-12);
	#endif


}

void PCB::Wrapper(){
	//cout<<"USO U VEPERRR"<<endl;
	 Nucleus::running->myThread->run();
	 //cout<<"IZASAO IZ RUNA"<<endl;
	 Lock();
	 Nucleus::running->WaitingOnMe->Unblock_All();//unblock all verovatno ne rai pa tu pukne, ali i dalje mislim da ne udje u run
	 Nucleus::running->state=PCB::FINISHED;
	 Unlock();
	 dispatch();
}


#include "PCB.h"
#include "Thread.h"
#include "PCBList.h"
#include <iostream.h>
#include <dos.h>

unsigned PCB::id=0;
PCB::PCB(unsigned long stackSize, unsigned int timeSlice, Thread *thread){
	sSize=stackSize/2;
	tSlice=timeSlice;
	myThread=thread;
	ID=++id;
	InitStack();
	state=CREATED;

}

PCB::~PCB(){
	myThread=0;
}

void PCB::InitStack(){
	stack=new unsigned[sSize];
	#ifndef BCC_BLOCK_IGNORE
	stack[sSize-1]=FP_SEG(myThread); //prvo mesto na steku=segment niti sa kojom je PCB u vezi
	stack[sSize-2]=FP_OFF(myThread); //drugo mesto na steku=offset niti sa kojom je PCB u vezi
	stack[sSize-5]=0x200; //dva prazna mesta zbog callback funkcije; postavljanje PSWI na 1
	stack[sSize-6]=FP_SEG(Wrapper); //postavljanje CS-a koji je jedak segmentu wrappera(Code segment, segment za PC)
	stack[sSize-7]=FP_OFF(Wrapper); //postavljanje IP-a koji je jednak offsetu wrappera(Instruction pointer, offset za PC)
	//ostaviti mesta za registre procesora pri ulasku u interrupt rutinu
	sp = FP_OFF(stack+sSize-16);
	bp = FP_OFF(stack+sSize-16);
	ss = FP_SEG(stack+sSize-16);
	#endif


}

 void PCB::Wrapper(){
	 myThread->run();
	 WaitingOnMe->Unblock_All();
	 state=PCB::FINISHED;
	 dispatch();
 }

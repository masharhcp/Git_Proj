#ifndef _PCB_H_
#define _PCB_H_

#include "Thread.h"
#include "PCBList.h"
class Thread;
class PCBList;

class PCB{
public:
	enum States{CREATED,READY,BLOCKED,FINISHED};
	States state;
	static unsigned id;
	unsigned ID;
	unsigned sp;
	unsigned ss;
	unsigned bp;
	unsigned  long sSize;
	unsigned int tSlice;
	unsigned int *stack;
	PCBList *WaitingOnMe;
	PCB *BlockedOn;
	Thread *myThread;


public:
	PCB(unsigned long stackSize, unsigned int timeSlice, Thread *thread );
	~PCB();
	void InitStack();
	static void Wrapper();


};
#endif

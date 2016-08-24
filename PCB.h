#ifndef _PCB_H_
#define _PCB_H_

#include "Thread.h"
#include "PCBList.h"
#include "Semaphor.h"
#include "KernSem.h"
class Thread;
class PCBList;
class Semaphore;
class KernelSem;

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
	int MaxBlockTime;
	int waitVal;
	PCBList *WaitingOnMe;
	PCB *BlockedOn;
	Thread *myThread;
	KernelSem *mySem;


public:
	PCB(unsigned long stackSize, unsigned int timeSlice, Thread *thread );
	~PCB();
	void InitStack();
	static void Wrapper();


};
#endif

#ifndef _PCB_H_
#define _PCB_H_

#include "Thread.h"
class Thread;

class PCB{
private:
	static unsigned id;
	unsigned ID;
	unsigned sp;
	unsigned ss;
	unsigned bp;
	unsigned  long sSize;
	unsigned int tSlice;
	unsigned* st1;
	unsigned state_new;
	unsigned state_finished;
	unsigned state_blocked;
	unsigned state_ready;
	unsigned state_running;
	Thread* myThread;
	int quantum;

public:
	PCB(unsigned long stackSize, unsigned int timeSlice, Thread *thread );
	void InitStack();
	static void Wrapper();


};
#endif

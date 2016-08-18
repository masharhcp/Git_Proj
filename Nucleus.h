
#ifndef _NUCLEUS_H_
#define _NUCLEUS_H_
#include "PCBList.h"
#include "IdleT.h"
#include "Thread.h"
#include "PCB.h"

typedef void interrupt (*interruptRoutine)(...);

class Nucleus{


public:

	Nucleus();
	~Nucleus();
	static void Inic_Timer();
	static void Restore_Timer();
	static void Start_System();
	static void Stop_System();
	static void interrupt Timer(...);
	//static interruptRoutine oldRoutine;
	static volatile PCB *running;
	static Thread *starting;
	static IdleT* idle;
	static int demand_context_change;
	static PCBList pcbs;
	static unsigned counter;

	friend class Thread;
	friend class PCB;

};


#endif


#ifndef _NUCLEUS_H_
#define _NUCLEUS_H_
#include "PCBList.h"
#include "IdleT.h"
#include "Thread.h"
#include "PCB.h"
#include "KernSem.h"
#include "SemList.h"
#include "PriQueue.h"
#include "IVTEntry.h"

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
	static IdleT *idle;
	static int demand_context_change;
	static PCBList *pcbs;
	static SemList *sems;
	static PriQueue *pcbQue;
	static unsigned counter;
	static unsigned clock;
	static IVTEntry* IVTTable[256];


	friend class Thread;
	friend class PCB;
	friend class KernelSem;
	friend class IVTEntry;
};


#endif

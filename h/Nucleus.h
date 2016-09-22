
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
#include "UserMain.h"

typedef void interrupt (*interruptRoutine)(...);
class PriQueue;
class PCBList;
class UserMain;



class Nucleus{


public:

	Nucleus();
	~Nucleus();
	static void Inic_Timer();
	static void Restore_Timer();
	static void Start_System();
	static void Stop_System();
	static void interrupt Timer(...);
	static void Unblock_Timed();
	static volatile PCB *running;
	static PCB *startingPCB;
	static Thread *starting;
	static IdleT *idle;
	static volatile int demand_context_change;
	static PCBList* pcbList;
	static SemList* sems;
	static PriQueue* pcbQueue;
	static volatile unsigned counter;
	static volatile unsigned long clock;
	static IVTEntry* IVTTable[256];
	static int test;
	static UserMain *umain;

	friend class Thread;
	friend class PCB;
	friend class KernelSem;
	friend class IVTEntry;
};


#endif

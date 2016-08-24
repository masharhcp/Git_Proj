/*
 * KernelSem.h
 *
 *  Created on: Aug 21, 2016
 *      Author: OS1
 */

#ifndef _KERNELSEM_H_
#define _KERNELSEM_H_
#include "PCB.h"
#include "PCBList.h"
typedef unsigned int Time;
class PCBList;

class KernelSem{
private:
	int value;
	PCBList *BlockedPCBs;

public:
	PCBList* Get_BlockedPCBs();
	int Get_Sem_Value();
	void Dec_Sem_Value();
	void Inc_Sem_Value();
	KernelSem(int val);
	int wait(Time maxTimeToWait);
	void signal();
	int val();
	void block(Time time);
	void unblock();
	~KernelSem();
};





#endif /* KERNELSEM_H_ */

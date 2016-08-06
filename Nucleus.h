
#ifndef _NUCLEUS_H_
#define _NUCLEUS_H_
#include "PCBList.h"



extern volatile int count;
extern PCBList pcbs;
extern PCB *running;
extern int demand_context_change=0;



class Nucleus{


public:
	Nucleus();
	~Nucleus();
	void Inic();
	void Restore();

};
void interrupt Timer();

#endif

#include "PCB.h"
#include "Thread.h"


int PCB::id=0;
PCB::PCB(unsigned long stackSize, unsigned int timeSlice, Thread *thread){
	sSize=stackSize;
	tSlice=timeSlice;
	myThread=thread;
	ID=++id;

}

PCB::~PCB(){}


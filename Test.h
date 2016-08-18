/*
 * Test.h
 *
 *  Created on: Aug 11, 2016
 *      Author: OS1
 */

#ifndef TEST_H_
#define TEST_H_
#include "Thread.h"
#include "Lock.h"
#include <iostream.h>

class BrzaNit: public Thread{
public:
	BrzaNit(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice):Thread(stackSize, timeSlice){};
	~BrzaNit(){waitToComplete();}
protected:
	virtual void run();
};

class SporijaNit: public Thread{
public:
	SporijaNit(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice):Thread(stackSize, timeSlice){};
	~SporijaNit(){waitToComplete();}
protected:
	virtual void run();
};



 void BrzaNit::run() {
	 SporijaNit *ss=new SporijaNit(4096, 17);
	 Lock();
	 cout<<"brza nit"<<endl;
	 Unlock();
	for (int i=0; i<30000; i++);
	ss->start();
	for (int j=0; j<30000; j++);
	delete ss;
}



 void SporijaNit::run() {
 	for (volatile long int i=0; i<70000; i++);
 	Lock();
 	cout<<"sporija nit"<<endl;
 	Unlock();
}


#endif /* TEST_H_ */

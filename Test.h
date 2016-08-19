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
	 Lock();
	 cout<<"brza nit"<<endl;
	 SporijaNit *ss=new SporijaNit(256, 20);
	 ss->start();
	 Unlock();
	 for (int j=0; j<5000; j++);
	 Lock();
	delete ss;
	Unlock();

}



 void SporijaNit::run() {

	for (int j=0; j<500; j++);
	Lock();
 	cout<<"sporija nit"<<endl;
 	Unlock();

}
	//for (int j=0; j<30000; j++);

#endif /* TEST_H_ */

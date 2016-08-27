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
 Semaphore* mutex = 0;


 class Znak : public Thread
 {
 public:
 	Znak(char znak, int n) : Thread(), znak(znak), n(n) {}
 	virtual ~Znak() { waitToComplete(); }

 void run()
 	{

 		for (long i = 0; i<100000; i++)
 		{
 				mutex->wait(1);
 				cout << znak <<" "<<i<<endl;
 				mutex->signal();

 		}

 		   mutex->wait(1);
 			cout << endl << znak << " finished" << endl;
 			mutex->signal();


 	}

 private:
 	char znak;
 	int n;

 };

#endif /* TEST_H_ */

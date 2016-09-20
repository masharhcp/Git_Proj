/*
 /** Test.h
 *
 *  Created on: Aug 11, 2016
 *      Author: OS1
 */

#ifndef TEST_H_
#define TEST_H_
#include "Thread.h"
#include "Lock.h"
#include "Event.h"
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>

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

 // 3 niti koje se vrte

 class Nit;

 Nit* a = 0;
 Nit* b = 0;
 Nit* c = 0;

 class Nit : public Thread {
 public:
 	Nit(char slovo, int n) : Thread(), slovo(slovo), n(n) {}
 	virtual ~Nit() { waitToComplete(); }

 	void run() {
 		for (long i = 0; i < 100000; i++) {

 			if(mutex->wait(3)){
 			cout << slovo;
 			mutex->signal();
 		}
 		}

 		if(mutex->wait(0)){
 		cout << endl << slovo << " finished" << endl;
 		mutex->signal();}

 		// if (slovo == 'a') b->waitToComplete();
 		// if (slovo == 'b') c->waitToComplete();
 		// if (slovo == 'c') a->waitToComplete();
 	}

 private:
 	char slovo;
 	int n;

 };

#endif TEST_H_

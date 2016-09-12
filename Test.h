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


 //PREPAREENTRY(9,1);


 Semaphore* mutex = 0;
 Semaphore* waitSem = 0;


 class Znak;

 Znak* a = 0;
 Znak* b = 0;
 Znak* c = 0;

 class Znak : public Thread {
 public:
 	Znak(char znak, int n) : Thread(), znak(znak), n(n) {}
 	virtual ~Znak() { waitToComplete(); }

 	void run() {
 		// for (long i = 0; i < 100000; i++) {
 		for (int i = 0; i < n; i++) {

 			if (mutex->wait(1)) {
 				cout << znak;
 				mutex->signal();

 			}

 			// mutex->wait(0);
 			// cout << znak;
 			// mutex->signal();

 			// for (int j = 0; j < 10000; j++)
 				// for (int k = 0; k < 10000; k++);
 			waitSem->wait(3);

 			// dispatch();
 		}

 		if (mutex->wait(1)) {
 			cout << endl << znak << " finished" << endl;
 			mutex->signal();
 		}

 		// mutex->wait(0);
 		// cout << endl << znak << " finished" << endl;
 		// mutex->signal();

 		// if (znak == 'a') b->waitToComplete();
 		// if (znak == 'b') c->waitToComplete();
 		// if (znak == 'c') a->waitToComplete();
 	}

 private:
 	char znak;
 	int n;

 };


 /*class Key : public Thread {
 public:
 	Key(int n) : Thread(), n(n) {}
 	virtual ~Key() { waitToComplete(); }

 	void run() {
 		Event e(9);

 		for (int i = 0; i < n; i++) {
 			mutex->wait(0);
 			cout << endl << "key waiting " << (i + 1) << endl;
 			mutex->signal();

 			e.wait();

 			mutex->wait(0);
 			cout << endl << "key continue " << (i + 1) << endl;
 			mutex->signal();
 		}

 		mutex->wait(0);
 		cout << endl << "key finished" << endl;
 		mutex->signal();
 	}

 private:
 	int n;

 };*/

#endif TEST_H_

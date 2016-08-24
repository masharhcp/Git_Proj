/*
 * Semaphor.cpp
 *
 *  Created on: Aug 21, 2016
 *      Author: OS1
 */
#include "Semaphor.h"
#include "KernSem.h"
#include "Lock.h"
class Semaphor;
class KernelSem;


Semaphore::Semaphore(int init){
	Lock();
	myImpl=new KernelSem(init);
	Unlock();
}

Semaphore::~Semaphore(){
	Lock();
	delete myImpl;
	Unlock();
}
int Semaphore::wait(Time maxTimeToWait){
	Lock();
	int ret=myImpl->wait(maxTimeToWait);
	Unlock();
	return ret;
}
void Semaphore::signal(){
	Lock();
	myImpl->signal();
	Unlock();
}
int Semaphore::val() const{
	return myImpl->val();
}




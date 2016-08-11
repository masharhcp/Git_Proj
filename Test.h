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
	BrzaNit(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	void run();
};

class SporijaNit: public Thread{
public:
	SporijaNit(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	void run();
};


#endif /* TEST_H_ */

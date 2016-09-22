
#ifndef _IDLET_H_
#define _IDLET_H_
#include "Thread.h"

class Thread;

class IdleT : public Thread{
private:
	int k;
public:
	IdleT();
	virtual void run();
	void start();
};


#endif

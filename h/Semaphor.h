#ifndef _SEMAPHOR_H_
#define _SEMAPHOR_H_
typedef unsigned int Time;

class KernelSem;
class Semaphore {
public:
	Semaphore(int init = 1);
	virtual ~Semaphore();
	virtual int wait(Time maxTimeToWait);
	virtual void signal();
	int val() const; // Returns the current value of the semaphore
protected:
	friend class Nucleus;
private:
	KernelSem* myImpl;
};
#endif

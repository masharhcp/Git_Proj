
#ifndef _IDLET_H_
#define _IDLET_H_

class IdleT : public Thread{
private:
	int k=1;
public:
	IdleT();
	virtual void run();
	void start();
};


#endif

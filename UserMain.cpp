#include "UserMain.h"
#include "user.h"
#include "Lock.h"
#include "Schedule.h"
#include "Nucleus.h"
#include "Test.h"

UserMain::UserMain(int c, char** v):Thread(defaultStackSize,1){
	argc=c;
	argv=v;
	ret=0;
}

void UserMain::run(){
	ret=userMain(argc, argv);
	//cout<<"Izaso iz userMain(argc, argv)"<<endl;
	/*mutex = new Semaphore(1);
	waitSem = new Semaphore(0);

		a = new Znak('a', 1000);
		b = new Znak('b', 1500);
		c = new Znak('c', 2000);
		//Key* k = new Key(50);

		a->start();
		b->start();
		c->start();
		//k->start();

		delete a;
		delete b;
		delete c;
		//delete k;

		if (mutex->wait(1)) {
			cout << endl << "userMain finished" << endl;
			mutex->signal();
		}

		// mutex->wait(0);
		// cout << endl << "userMain finished" << endl;
		// mutex->signal();

		delete waitSem;
		delete mutex;

		//ret=0;*/
}

UserMain::~UserMain(){
	Lock();
	waitToComplete();
	Unlock();
}






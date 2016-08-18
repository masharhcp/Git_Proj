#include "Thread.h"
#include "Lock.h"
#include <iostream.h>
class Thread;

/*class BrzaNit: public Thread{
public:
	BrzaNit(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice):Thread(stackSize, timeSlice){};
	~BrzaNit(){waitToComplete();}
protected:
	virtual void run();
};

class SporijaNit: public Thread{
public:
	SporijaNit(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	virtual void run();
};



 void BrzaNit::run() {
	 cout<<"USO U RUN"<<endl;
		for (int i=0; i<7000; i++);
		cout<<"Zavrsih run, ja sam brza nit"<<endl;
}


 SporijaNit::SporijaNit(StackSize stackSize, Time timeSlice):Thread(stackSize, timeSlice){
	 cout<<"Napravili su me, ja sam spora nit"<<endl;
 }
 	 void SporijaNit::run() {
 		for (volatile int i=0; i<200; i++){}
 		Lock();
 		cout<<"Zavrsih run, ja sam sporija nit"<<endl;
 		Unlock()
 	}*/

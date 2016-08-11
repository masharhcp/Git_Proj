#include "Test.h"
#include "Lock.h"

BrzaNit::BrzaNit(StackSize stackSize, Time timeSlice):Thread(stackSize, timeSlice){
	cout<<"Napravili su me, ja sam brza nit"<<endl;
}
 void BrzaNit::run() {
		for (volatile int i=0; i<5; i++){}
		Lock();
		cout<<"Zavrsih run, ja sam brza nit"<<endl;
		Unlock()
	}


 SporijaNit::SporijaNit(StackSize stackSize, Time timeSlice):Thread(stackSize, timeSlice){
	 cout<<"Napravili su me, ja sam spora nit"<<endl;
 }
 	 void SporijaNit::run() {
 		for (volatile int i=0; i<200; i++){}
 		Lock();
 		cout<<"Zavrsih run, ja sam sporija nit"<<endl;
 		Unlock()
 	}

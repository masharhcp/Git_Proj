#ifndef _EVENT_H_
#define _EVENT_H_
#include "IVTEntry.h"
#include "Nucleus.h"

typedef unsigned char IVTNo;
class KernelEv;

class Event {
public:
	Event(IVTNo ivtNo);
	~Event();
	void wait();
protected:
	friend class KernelEv;
	void signal(); // can call KernelEv
private:
	KernelEv* myImpl;
};



#define PREPAREENTRY(numEntry, callOld)\
void interrupt inter##numEntry(...);\
IVTEntry newEntry##numEntry(numEntry,&inter##numEntry);\
void interrupt inter##numEntry(...){\
newEntry##numEntry.signal();\
if (callOld == 1)\
newEntry##numEntry.callOldR();\
}
#endif


//newEntry##numEntry.callOldR();\
//newEntry##numEntry.signal();\
//Nucleus::IVTTable[numEntry]->oldR();\
//dispatch();\
//Nucleus::IVTTable[numEntry]->myKernelEv->signal();\

#include "Event.h"
#include "Lock.h"

	Event::Event(IVTNo ivtNo){
		Lock();
		myImpl=new KernelEv(ivtNo);
		Unlock();
	}

	Event::~Event(){
		Lock();
		delete myImpl;
		Unlock();
	}

	void Event::wait(){
		Lock();
		myImpl->wait();
		Unlock();
	}

	void Event::signal(){
		Lock();
		myImpl->signal();
		Unlock();
	}






#include "IdleT.h"

IdleT::IdleT():Thread(256 ,0){}

void IdleT::run(){
	k=1;
	while (k==1){}
}

void IdleT::start(){
	run();
}


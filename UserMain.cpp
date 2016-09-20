#include "UserMain.h"
//#include "user.h"
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

}

UserMain::~UserMain(){
	Lock();
	waitToComplete();
	Unlock();
}






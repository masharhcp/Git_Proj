#include "UserMain.h"


UserMain::UserMain(int c, char** v):Thread(defaultStackSize,1){
	argc=c;
	argv=v;
}

void UserMain::run(){}





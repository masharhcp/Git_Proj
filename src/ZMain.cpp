#include "Nucleus.h"
#include <iostream.h>
#include "PriQueue.h"
#include "PCBList.h"
#include "PCB.h"
#include "UserMain.h"
#include "Lock.h"
#include "Nucleus.h"
class PriQueue;
class PCB;
class PCBList;
class UserMain;



int main(int argc, char* argv[]) {
	int val;
	Nucleus::Start_System(); //ubacuje moju prekidnu rutinu, pravi sve neophodne niti (starting koja ce predstavljati pocetni kontekst main-a, idle);
							//alocira sve neophodne strukture
	Nucleus::umain=new UserMain(argc,argv);
	Nucleus::umain->start();
	Nucleus::umain->waitToComplete();
	val=Nucleus::umain->ret;
	delete Nucleus::umain;
	Nucleus::Stop_System();//vraca staru prekidnu rutinu
							//dealocira koriscene strukture
	return val;


}


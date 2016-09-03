#include "Nucleus.h"
#include "Test.h"
#include <iostream.h>
#include "PriQueue.h"
#include "PCBList.h"
#include "PCB.h"
#include "UserMain.h"
#include "Lock.h"
class PriQueue;
class PCB;
class BrzaNit;
class PCBList;



int main(int argc, char* argv[]) {

Nucleus::Start_System();
UserMain *u=new UserMain(argc,argv);
u->start();
BrzaNit *i= new BrzaNit();
u->waitToComplete();
int ret=u->ret;
delete u;
Nucleus::Stop_System();
return ret;

}


//o[m-20]=new BrzaNit(256, m);
//o[m-20]->start();
//delete o[l-12];
//p[m-20]=new SporijaNit(256, m);
		//p[m-20]->start();
//SporijaNit *p[12];
/*for (volatile int k = 0; k<10000; ++k);
	       			for (volatile int j = 0; j <30000; ++j);
 SporijaNit *sn1=new SporijaNit(256, 40);
    BrzaNit *bn1=new BrzaNit(256, 80);
    bn1->start();
    sn1->start();
    delete bn1;
    delete sn1;*/






//MAIN
/*	cout<<"Poceo sam"<<endl;
Nucleus::Start_System();
BrzaNit *p[500];

	for (int m=20; m<520; m++){
		Lock();
		//cout<<m-20<<endl;
		p[m-20]=new BrzaNit(256, m);
		p[m-20]->start();
		Unlock();

	}

	for (int l=20; l<520; l++){
		Lock();
		//cout<<l-20<<endl;
		delete p[l-20];
		Unlock();
		}


cout<<"Poceo sam"<<endl;


Nucleus::Stop_System();

return 1;*/


/*TEST ZA PRIQUEUE
 PriQueue* lista=new PriQueue();
PCB* pcb1=new PCB(256, 5, 0);
PCB* pcb2=new PCB(256, 7, 0);
PCB* pcb3=new PCB(256, 8, 0);
PCB* pcb4=new PCB(256, 8, 0);
lista->Add(pcb3, 20);
lista->Add(pcb2, 19);
lista->Add(pcb4, 23);
lista->Add(pcb1, 22);
lista->Print();

lista->Remove_By_ID(3);
cout<<"treca"<<endl;
lista->Print();*/



/*TEST ZA PCBList
 PCBList* lista=new PCBList();
PCB* pcb1=new PCB(256, 5, 0);
PCB* pcb2=new PCB(256, 5, 0);
PCB* pcb3=new PCB(256, 5, 0);
PCB* pcb4=new PCB(256, 5, 0);
PCB* pcb5=new PCB(256, 5, 0);

lista->Add(pcb3);
lista->Add(pcb5);
cout<<"prvi print"<<endl;
lista->Print();
lista->Add(pcb2);
lista->Remove_First();
cout<<"drugi print"<<endl;
lista->Print();
lista->Add(pcb1);
lista->Add(pcb4);
cout<<"treci print"<<endl;
lista->Print();
lista->Remove_By_ID(4);
cout<<"cetvrti print"<<endl;
lista->Print();
lista->Remove_By_ID(0);
cout<<"peti print"<<endl;
lista->Print();
lista->Remove_By_ID(3);
cout<<"sesti print"<<endl;
lista->Print();*/


//TEST ZA SEM
/*mutex = new Semaphore(1);

		Znak* a = new Znak('a', 10);
		Znak* b = new Znak('b', 15);
		Znak* c = new Znak('c', 20);



		a->start();
		b->start();
		c->start();



		delete a;
		delete b;
		delete c;



		mutex->wait(1);
			Lock();
			cout << endl << "userMain finished" << endl;
			Unlock();
			mutex->signal();


		delete mutex;*/

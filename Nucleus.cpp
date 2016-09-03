#include "Nucleus.h"
#include "Lock.h"
#include "schedule.h"
#include <dos.h>
#include <stdlib.h>
#include <iostream.h>

PCBList *Nucleus::pcbList=0;
SemList *Nucleus::sems=0;
PriQueue *Nucleus::pcbQueue=0;
volatile PCB* Nucleus::running = 0;
PCB* Nucleus::startingPCB = 0;
Thread* Nucleus::starting = 0;
IdleT* Nucleus::idle = 0;
int Nucleus::demand_context_change = 0;
unsigned Nucleus::counter;
volatile unsigned long Nucleus::clock;
int Nucleus::test=0;
volatile unsigned tsp,tbp,tss;
IVTEntry* Nucleus::IVTTable[256];

/*extern PriQueue* pcbQueue=0;
extern PCBList* pcbList=0;*/


void Nucleus::Inic_Timer(){
#ifndef BCC_BLOCK_IGNORE
	void interrupt (*oldRoutine)(...) = getvect(0x08);
	setvect(0x08, Timer);
	setvect(0x60, oldRoutine);
#endif
}
void Nucleus::Restore_Timer(){
#ifndef BCC_BLOCK_IGNORE
	void interrupt (*oldRoutine)(...) = getvect(0x60);
	setvect(0x08, oldRoutine);
#endif
}


void Nucleus::Start_System(){
	Lock();
	Inic_Timer();
	Nucleus::pcbQueue=new PriQueue();
	Nucleus::sems=new SemList();
	Nucleus::pcbList=new PCBList();
	starting=new Thread(0x1000, 10);
	starting->myPCB->state=PCB::READY;
	startingPCB=starting->myPCB;
	running=starting->myPCB;
	counter=running->tSlice;
	idle=new IdleT();
	idle->start();

	Unlock();
}

void Nucleus::Stop_System(){
	Lock();
	Restore_Timer();
	delete starting;
	delete idle;
	delete sems;
	delete pcbList;
	delete pcbQueue;

	Unlock();

}


PCB* curr=0;
void interrupt Nucleus::Timer(...){

	if (!demand_context_change && counter>0) {--counter; }
	if (!demand_context_change){
		++clock;

	while ((pcbQueue->head!=0) && (pcbQueue->Get_First()!=0) && (pcbQueue->Get_First_TTW()<=clock)){

		curr=pcbQueue->Remove_First();
		if (curr!=0){
		curr->state=PCB::READY;
		curr->waitVal=0;
		curr->MaxBlockTime=-1;
		curr->mySem->Get_BlockedPCBs()->Remove_By_ID(curr->ID);
		curr->mySem->Inc_Sem_Value();
		curr->mySem=0;
		Scheduler::put(curr);
		}
	}
}

	//ako nije zahtevana promena konteksta i ako nit nema pravo da se izvrsava beskonacno
		if ((Nucleus::counter == 0 && running->tSlice!=0) || demand_context_change){
			//ako je zahtevana promena konteksta ili je nit dosla do nule (njen brojac)
			// cout<<"menjam kontekst"<<endl;
				demand_context_change=0;
			asm {
				// cuva sp
				mov tsp, sp
				mov tss, ss
				mov tbp, bp
			}

			running->sp = tsp;
			running->ss = tss;
			running->bp = tbp;


			if ((running->state==PCB::READY)&&(running!=idle->myPCB)) Scheduler::put((PCB*)running);

	        running=Scheduler::get();
	        if (running==0||running->state==PCB::FINISHED)running=idle->myPCB;

			tsp = running->sp;
			tss = running->ss;
			tbp = running->bp;
			Nucleus::counter = running->tSlice;

			asm {
				mov sp, tsp   // restore sp
				mov ss, tss
				mov bp, tbp
			}


	}
		// poziv stare prekidne rutine koja se
	     // nalazila na 08h, a sad je na 60h
	     // poziva se samo kada nije zahtevana promena
	     // konteksta – tako se da se stara
	     // rutina poziva samo kada je stvarno doslo do prekida
	if(!demand_context_change) {asm int 60h;
	/*tick();*/}

	demand_context_change = 0;
};




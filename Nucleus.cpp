#include "Nucleus.h"
#include "Lock.h"
#include "schedule.h"
#include <dos.h>
#include <stdlib.h>
#include <iostream.h>

PCB* Nucleus::running = NULL;
Thread* Nucleus::starting = NULL;
IdleT* Nucleus::idle = NULL;
int Nucleus::demand_context_change = 0;
PCBList Nucleus::pcbs;
unsigned Nucleus::counter;


void Nucleus::Inic_Timer(){
	void interrupt (*oldRoutine)(...) = getvect(0x08);
	setvect(0x08, Timer);
	setvect(0x60, oldRoutine);

}
void Nucleus::Restore_Timer(){
	void interrupt (*oldRoutine)(...) = getvect(0x60);
	setvect(0x08, oldRoutine);

}


void Nucleus::Start_System(){
	Lock();
	Inic_Timer();
	starting=new Thread(0x1000, 10);
	starting->myPCB->state=PCB::READY;
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
	Unlock();

}

void interrupt Nucleus::Timer(...){

 volatile unsigned tsp,tbp,tss;

	if (!demand_context_change && running->tSlice!=0) {--(Nucleus::counter);  cout<<Nucleus::counter<<endl;}; //ako nije zahtevana promena konteksta i ako nit nema pravo da se izvrsava beskonacno
		if ((Nucleus::counter == 0 && running->tSlice!=0) || demand_context_change) { //ako je zahtevana promena konteksta ili je nit dosla do nule (njen brojac)

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
	        if (running==0)running=idle->myPCB;

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
	     // konteksta � tako se da se stara
	     // rutina poziva samo kada je stvarno doslo do prekida
	if(!demand_context_change) asm int 60h;

	demand_context_change = 0;
};



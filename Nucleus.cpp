#include "Nucleus.h"
#include "Lock.h"
#include "schedule.h"
#include <dos.h>
#include <stdlib.h>


PCB* Nucleus::running = NULL;
Thread* Nucleus::starting = NULL;
IdleT* Nucleus::idle = NULL;
int Nucleus::demand_context_change = 0;
PCBList Nucleus::pcbs;
unsigned Nucleus::counter;

void Nucleus::Inic_Timer(){


}
void Nucleus::Restore_Timer(){

}


void Nucleus::Start_System(){
	Lock();
	Inic_Timer();
	starting=new Thread();
	starting->myPCB->state=PCB::READY;
	running=starting->myPCB;
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

void interrupt Nucleus::Timer(){

 volatile unsigned tsp,tbp,tss;
	if (!demand_context_change) --(Nucleus::counter);
		if (Nucleus::counter == 0 || demand_context_change) {

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


	        if (!running->state==PCB::FINISHED)
	        	Scheduler::put((PCB*)running);
	        running=Scheduler::get();
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
	if(!demand_context_change) asm int 60h;

	demand_context_change = 0;
};




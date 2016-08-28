/*
 * KernelEv.h
 *
 *  Created on: Aug 26, 2016
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_

#include "PCB.h"
typedef unsigned char IVTNo;

class KernelEv{
public:
	KernelEv(IVTNo ivtN);
	~KernelEv();
    void signal();
    void wait();

private:
    int value;
	IVTNo ivtNo;
	PCB* maker;
};




#endif /* KERNELEV_H_ */

/*
 * PriQueue.h
 *
 *  Created on: Aug 22, 2016
 *      Author: OS1
 */

#ifndef _PRIQUEUE_H_
#define _PRIQUEUE_H_

#include "PCB.h"
class PCB;

class PriQueue{
private:
	struct Node{
			PCB* Data;
			int TimeToWait;
			Node* Next;
			Node(PCB *d, int time): Data(d), Next(0), TimeToWait(time){}
		};

	Node *head, *tail;

public:
	PCB* Get_First();
	PCB* Remove_First();
	void Add(PCB* p, int time);
	PCB* Remove_By_ID(int ID);
	void Print();
	PriQueue();
	~PriQueue();

};



#endif /* _PRIQUEUE_H_ */

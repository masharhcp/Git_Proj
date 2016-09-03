/*
 * PCBList.h
 *
 *  Created on: Aug 3, 2016
 *      Author: OS1
 */

#ifndef _PCBLIST_H_
#define _PCBLIST_H_
#include "PCB.h"
class PCB;
class PCBList{

public:
	struct Node{
		PCB* Data;
		Node* Next;
		Node(PCB *d): Data(d), Next(0){}
	};

	Node *head, *tail;

public:
	PCBList():head(0),tail(0){}
	~PCBList();
	void Add(PCB* data);
	void Remove_First();
	void Remove_By_ID(unsigned ID);
	PCB* Get_First();
	PCB* Get_By_ID(unsigned ID);
	void Unblock_All();
	void Print();

};




#endif

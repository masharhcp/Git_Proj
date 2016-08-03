/*
 * PCBList.h
 *
 *  Created on: Aug 3, 2016
 *      Author: OS1
 */

#ifndef _PCBLIST_H_
#define _PCBLIST_H_

class List{
	struct Node{
		PCB* Data;
		Node* Next;
		Node(Data *d, Node *n =nullptr): Data(d), Next(n){}
		~Node() { delete Data; delete Next; }
	};

public:
	List();
	void Add(PCB* data);
	PCB* Get();

};




#endif

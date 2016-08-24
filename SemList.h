/*
 * SemList.h
 *
 *  Created on: Aug 22, 2016
 *      Author: OS1
 */

#ifndef _SEMLIST_H_
#define _SEMLIST_H_

#include "KernSem.h"


class KernelSem;
class SemList{
private:
	struct Node{
		KernelSem* Data;
		Node* Next;
		Node(KernelSem *d): Data(d), Next(0){}
	};

	Node *head, *tail;

public:
	SemList();
	~SemList();
	void Add(KernelSem* data);
	void Remove_First();
	KernelSem* Get_First();



};




#endif /* SEMLIST_H_ */

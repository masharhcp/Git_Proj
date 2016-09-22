/*
 * SemList.cpp
 *
 *  Created on: Aug 22, 2016
 *      Author: OS1
 */
#include "SemList.h"
#include "KernSem.h"
#include "Lock.h"


SemList::SemList(){
	head=0;
	tail=0;
}

SemList::~SemList(){
	Node* curr;
	curr=head;
    while(head!=0){
    	head=head->Next;
    	curr->Next=0;
    	curr->Data=0;
    	delete curr;
    	curr=head;
    }
    head=0;
    tail=0;
}

void SemList::Add(KernelSem* data){
	if (head==0){
		head=new Node(data);
	}
	else{
		tail->Next=new Node(data);
	}
	tail=tail->Next;
}

void SemList::Remove_First(){
	Node* curr;
	curr=head;
	if(head->Next!=0){
	head=head->Next;}
	else {
		head=0;
		tail=0;
	}
	delete curr;

}


KernelSem* SemList::Get_First(){
	Node *curr=head;
	if (curr==0) return 0;

		return curr->Data;
}


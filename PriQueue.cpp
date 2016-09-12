/*
 * PriQueue.cpp
 *
 *  Created on: Aug 22, 2016
 *      Author: OS1
 */

#include "PriQueue.h"
#include "PCB.h"
#include "Nucleus.h"
#include <iostream.h>

void PriQueue::Add(PCB* p, int time){
	p->MaxBlockTime=time;
	int k=time+Nucleus::clock;
	Node *addNode=new Node(p, k);
	Node *curr, *prev;
	curr=head;
	prev=0;

	if (head==0){
		head=tail=addNode;
	}
	else{
		while (curr && curr->TimeToWait<addNode->TimeToWait){
			prev=curr;
			curr=curr->Next;
		}
		if (!prev){
			addNode->Next=head;
			head=addNode;
		}
		else
		if (!curr){
			tail->Next=addNode;
			tail=addNode;
		}
		else{
			prev->Next=addNode;
			addNode->Next=curr;

		}
	}

}

int PriQueue::Get_First_TTW(){
	return head->TimeToWait;

}

PCB* PriQueue::Get_First(){
 return head->Data;

}


PCB* PriQueue::Remove_First(){
	Node *curr;
	PCB *hel;
	curr=head;
	hel=head->Data;
	if(head==0){
		return 0;
	}
	else
	if (head->Next){
		head=head->Next;
	}
	else{
		head=0; tail=0;
	}
	curr->Next=0;
	delete curr;
	return hel;

}

PCB* PriQueue::Remove_By_ID(int ID){
	Node *curr, *prev=0;
	PCB *hel;
	curr=head;
	if (!head) return 0;
	while ((ID!=curr->Data->ID) && curr){
		prev=curr;
		curr=curr->Next;
	}
	if (!curr)return 0;
	hel=curr->Data;

	if (!prev){
		head=head->Next;
		if (!head)tail=0;
		delete curr;
		return hel;
	}
	else
	if (curr==tail){
		tail=prev;
		prev->Next=0;
		delete curr;
		return hel;
	}
	else {
		prev->Next=curr->Next;
		delete curr;
		return hel;
	}


}//PROVERI OVO OBAVEZNO


PriQueue::~PriQueue(){
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

void PriQueue::Print(){
	Node* curr=head;

	cout<<endl<<"list"<<endl;
	if (head!=0){
	while (curr->Data && curr!=0){
		cout<<"MBT:"<<curr->Data->MaxBlockTime<<"TTW: "<<curr->TimeToWait<<" ID:"<<curr->Data->ID<<endl;
		curr=curr->Next;
	}
	}

}


#include "PCBList.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "Lock.h"
#include <iostream.h>



void PCBList::Add(PCB* data){
	Node *addNode=new Node(data);
	if (head==0){
		head=addNode;
		tail=head;
	}
	else{
		tail->Next=addNode;
		tail=addNode;
	}

}

void PCBList::Remove_First(){
	Node* curr;
	curr=head;
	if (head!=0){
	if(head->Next!=0){
	head=head->Next;
	}
	else {
		head=0;
		tail=0;
	}
	curr->Data=0;
	delete curr;
	}
}

void PCBList::Remove_By_ID(unsigned int ID){
	Node *curr, *prev;
	curr=head;
	prev=0;
	if (curr!=0){
	while (curr && curr->Data->ID!=ID){
		prev=curr;
		curr=curr->Next;
	}
			if (curr==head){
				if (head==tail){head=0; tail=0; delete curr;}
				else{
				head=head->Next;
				curr->Next=0;
				delete curr;
				}
			}
			else {
				if (curr==tail){
					tail=prev;
					tail->Next=0;
					delete curr;
				}

				else{
					prev->Next=curr->Next;
					curr->Next=0;
					delete curr;
				}
			}

		}

	}



PCB* PCBList::Get_First(){
	Node *curr=head;
	if (curr==0) return 0;
	return curr->Data;
}

PCB* PCBList::Get_By_ID(unsigned int ID){
	Node* curr;
	curr=head;
	while (curr){
		if (curr->Data->ID==ID)return curr->Data;
	}
	return 0;
}

void PCBList::Unblock_All(){

		Node* curr;
		curr=head;
	    while(head!=0){
	    	head=head->Next;
	    	curr->Data->state=PCB::READY;
	    	curr->Data->BlockedOn=0;
	    	Scheduler::put(curr->Data);
	    	curr->Next=0;
	    	curr->Data=0;
	    	delete curr;
	    	curr=head;
	    }
	    head=0;
	    tail=0;


}

PCBList::~PCBList(){
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

void PCBList::Print(){
	Node* curr=head;
	while (curr){
		cout<<"ID: "<<curr->Data->ID<<endl;
		curr=curr->Next;
	}
}

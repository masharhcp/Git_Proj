
#include "PCBList.h"
#include "PCB.h"
#include "SCHEDULE.H"

PCBList::PCBList(){
	head=0;
	tail=0;
}

PCBList::~PCBList(){
	Node* it;
	it=head;
    while(head){
    	head=head->Next;
    	it->Next=0;
    	delete it;
    	it=head;
    }
    head=0;
    tail=0;
}

void PCBList::Add(PCB* data){
	if (head==0){
		head=new Node(data);
	}
	else{
		tail->Next=new Node(data);
	}
	tail=tail->Next;
}

void PCBList::Remove_First(){
	Node* help;
	help=head;
	if(head->Next!=0){
	head=head->Next;}
	else {
		head=0;
		tail=0;
	}
	delete help;

}

void PCBList::Remove_By_ID(unsigned int ID){
	Node* it, *prev;
	it=head;
	prev=0;
	while (it){
		if (it->Data->ID==ID){
			if (it==head){
				if (head==tail){head=0; tail=0; delete it;}
				else{
				head=head->Next;
				}
			}
			else {
				if (it==tail){
					tail=prev;
					tail->Next=0;
					delete it;
				}

				else{
					prev->Next=it->Next;
					it->Next=0;
					delete it;
				}
			}
		}
		else{
			prev=it;
			it=it->Next;
		}
	}
}

PCB* PCBList::Get_First(){
	return head->Data;
}

PCB* PCBList::Get_By_ID(unsigned int ID){
	Node* it;
	it=head;
	while (it){
		if (it->Data->ID==ID)return it->Data;
	}
	return 0;
}

void PCBList::Unblock_All(){
	Node* p;
	p=head;
	while(p){
		p->Data->state=PCB::READY;
		Scheduler::put(p->Data);
	}


};

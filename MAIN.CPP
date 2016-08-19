#include "Nucleus.h"
#include "Test.h"
#include <iostream.h>
class BrzaNit;
//int argc, char* argv[]


int main() {
	cout<<"Poceo sam"<<endl;
Nucleus::Start_System();
BrzaNit *p[500];

	for (int m=20; m<520; m++){
		Lock();
		//cout<<m-20<<endl;
		p[m-20]=new BrzaNit(256, m);
		p[m-20]->start();
		Unlock();

	}

	for (int l=20; l<520; l++){
		Lock();
		//cout<<l-20<<endl;
		delete p[l-20];
		Unlock();
		}


cout<<"Poceo sam"<<endl;


Nucleus::Stop_System();

return 1;
}


//o[m-20]=new BrzaNit(256, m);
//o[m-20]->start();
//delete o[l-12];
//p[m-20]=new SporijaNit(256, m);
		//p[m-20]->start();
//SporijaNit *p[12];
/*for (volatile int k = 0; k<10000; ++k);
	       			for (volatile int j = 0; j <30000; ++j);
 SporijaNit *sn1=new SporijaNit(256, 40);
    BrzaNit *bn1=new BrzaNit(256, 80);
    bn1->start();
    sn1->start();
    delete bn1;
    delete sn1;*/

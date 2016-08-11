#include "Nucleus.h"
#include "Test.h"
#include <iostream.h>

//int argc, char* argv[]


int main() {
	cout<<"Poceo sam"<<endl;
	Nucleus::Start_System();

	SporijaNit *sn1=new SporijaNit(256, 40);
    BrzaNit *bn1=new BrzaNit(256, 80);
    bn1->start();

    for (volatile int k = 0; k<10000; ++k)
       			for (volatile int j = 0; j <30000; ++j);

	//sta se desava ovde??

    delete bn1;
    delete sn1;
	Nucleus::Stop_System();
	cout<<"Zavrsio sam"<<endl;
return 1;
}



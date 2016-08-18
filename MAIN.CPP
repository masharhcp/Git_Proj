#include "Nucleus.h"
#include "Test.h"
#include <iostream.h>
class BrzaNit;
//int argc, char* argv[]


int main() {
	cout<<"Poceo sam"<<endl;
	Nucleus::Start_System();
	for (volatile int k = 0; k<10000; ++k)
	       			for (volatile int j = 0; j <30000; ++j);
	SporijaNit *sn1=new SporijaNit(256, 40);
    BrzaNit *bn1=new BrzaNit(256, 80);
    bn1->start();
    sn1->start();


	//sta se desava ovde??

    delete bn1;
    delete sn1;


Nucleus::Stop_System();

return 1;
}



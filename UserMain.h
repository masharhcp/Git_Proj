/*
 * UserMain.h
 *
 *  Created on: Aug 5, 2016
 *      Author: OS1
 */

#ifndef _USERMAIN_H_
#define _USERMAIN_H_

#include "Thread.h"

class UserMain :public Thread{

private:
	char** argv;
	int argc;
	void run();

public:
	UserMain(int, char**);
};




#endif

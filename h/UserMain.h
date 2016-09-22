/*
 * UserMain.h
 *
 *  Created on: Aug 5, 2016
 *      Author: OS1
 */

#ifndef _USERMAIN_H_
#define _USERMAIN_H_

#include "Thread.h"

int userMain(int,char**);
class UserMain :public Thread{

private:
	char** argv;
	int argc;
	virtual void run();

public:
	int ret;
	UserMain(int, char**);
	~UserMain();
};



#endif

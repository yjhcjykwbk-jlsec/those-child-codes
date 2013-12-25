#include <stdio.h>
#ifndef _a_
#define _a_
static int a=1;
#endif

#ifndef _bh_
#include "b.h"
#define _bh_
#endif   

#ifndef _oh_
#include "o.h"
#define _oh_
#endif

class MyA{
public :
	MyA(){}
	void func();
	void _func();
};

//void globlfunc(){return;}
//int globlvar;
static int globlvar;
class globlclass{
	int funcInGloblClass(){return 1;}
	};
//defined in b.cpp
extern void main_t();
//defined in a1.cpp
extern void main_s();
#ifndef _bh_
#define _bh_
#include "b.h"
#endif

void MyB::func(){
	printf("MyB::func:this is used by MyA::func,and if you include a.h to use MyA::func, you need to include this b.obj too\n");
	//printf("if a.h include b.h,  you only need to include a.h,not b.h, the linker will link vars for emp MyB::func recursively for you.\n");
	}
void main_t(){
	printf ("main_t:from b.cpp,externed by a.h ,used by a1.cpp and a2.cpp\n");
	}
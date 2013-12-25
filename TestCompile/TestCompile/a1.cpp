//#ifndef _ah_
//#define _ah_
#include "a.h"
//#endif

//you can include b.h to use MyB in a.h,then you donot need to include b.h here
//#ifndef _bh_
//#define _bh_
//////////////////////////////#include "b.h"
//#endif

void MyA::func(){
	printf("func: declared from a.h and defined in a1.cpp\n");
	//_func is in a2.obj,not in this a1.obj  ,anyone include a1.obj to use api func will need to include  a2.obj too.
	_func();
	printf("now func will use MyB:\n");
	MyB b=MyB();
	b.func();
	}


void main_s(){
	//当a1.cpp定义一个全局符号的时候，任何h或cpp都可以extern它。包括a1.cpp所引用的a.h。这时候他们都成为符号使用者。
	printf ("main_s:from a1.cpp,externed by a.h ,used by a2.cpp\n");
	}
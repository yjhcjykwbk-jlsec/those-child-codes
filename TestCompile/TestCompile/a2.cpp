//#ifndef _ah_
//#define _ah_
#include "a.h"
//#endif

//you can include b.h to use b in a.h,then you donot need to include b.h here
//#ifndef _bh_
//#define _bh_
///////////////////////////#include "b.h"
//#endif


void MyA::_func(){
	printf("_func:this function is declared from a.h and defined in a2.cpp\n");
	printf("a1.cpp and a2.cpp , will generate a1.obj and a2.obj using a.h\n");
	printf("in a2.cpp which include a.h,a.h include b.h,and the value b from b.h is %d\n",b);
	printf("in a2.cpp which include a.h,a.h include o.h,and the value o from o.h is %d\n",o);

		main_t();
		main_s();
	}

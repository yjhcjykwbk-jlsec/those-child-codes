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
	//��a1.cpp����һ��ȫ�ַ��ŵ�ʱ���κ�h��cpp������extern��������a1.cpp�����õ�a.h����ʱ�����Ƕ���Ϊ����ʹ���ߡ�
	printf ("main_s:from a1.cpp,externed by a.h ,used by a2.cpp\n");
	}
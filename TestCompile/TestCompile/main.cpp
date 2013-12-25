#ifndef _stdio_
#define _stdio_
#include <stdio.h>
#endif

//#ifndef _ah_
#include "a.h"
////#include "test/d.h"
#include "d.h"
//#include "test/d.h"
//#define _ah_
//#endif

//#ifndef _bh_
//#define _bh_
///////////////#include "b.h"
//#endif

void func(char *str){
 	//return SysAllocString(str);
}

int main(char *argc,char *argv[]){
	printf("main:this is a:%d from a.h\n",a);
	printf("main:this is b:%d from b.h\n",b);

	printf("main:this is a:%d from a.h\n",a);
	printf("main:this is a:%d from a.h\n",a);
	MyA at=MyA();
	at.func();
	
	printf("main:this is from c.h:%d\n",s);
	//d();
	//Ind();
	// Outd();
	scanf("%d",&a);
	return 1;
	//return 1;
	}
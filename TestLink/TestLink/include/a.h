#include <stdio.h>
#ifndef _a_
#define _a_
static int a=1;
#endif
	  /*
#ifndef _bh_
#include "b.h"
#define _bh_
#endif   */

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
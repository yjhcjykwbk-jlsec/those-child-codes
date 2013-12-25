#include <linux/module.h>
void bcopy(unsigned char *src,unsigned char *des,int count)	{
	int i=0;
	for (i=0;i<count;i++)
	{
	    printk("src[%d]=%x\n",i,src[i]);
	    des[i]=src[count-i];
	}
}
void get_CPUID()
{
    // 定义一些变量，用于存储 CPU 的 ID信息
    char szCpu[16]={0};
	unsigned int szCpu0,szCpu1,szCpu2;
    unsigned int uCpuID;
	int i = 0;
    __asm__ __volatile__(
      "push %%ebx;"
      "push %%ecx;"
      "push %%edx;"
      "mov $0, %%eax;"
      "cpuid;"
      "mov %%ebx, %0;"
      "mov %%edx, %1;"
      "mov %%ecx, %2;"
      "mov $1, %%eax;"
	  "cpuid;"
      "mov %%edx, %3;"
      "pop %%ebx;"
      "pop %%ecx;"
      "pop %%edx;"
      :"=r"(szCpu0),"=r"(szCpu1),"=r"(szCpu2),"=r"(uCpuID)
      :
    );
  printk("szCpu0=%x,szCpu1=%x,szCpu2=%x\n",szCpu0, szCpu1, szCpu2);
  bcopy((unsigned char *)&szCpu0,(unsigned char *)szCpu,4);
  bcopy((unsigned char *)&szCpu1,(unsigned char *)(szCpu+4),4);
  bcopy((unsigned char *)&szCpu2,(unsigned char *)(szCpu+8),4);
  for(i = 0; i < 16; i++)
    printk("szCpu[%d]=%c\n",i,szCpu[i]);
    printk("cpu id is %u, info is %s\n", uCpuID,szCpu);
}
static int __init mymodule_init(void)
{
	printk("Hello Kernel\n");
	get_CPUID();
	return 0;
}
static void __exit mymodule_exit(void)
{
	printk ("Unloading my module.\n");
	return;
}



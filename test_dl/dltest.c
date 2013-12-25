#include <dlfcn.h>
#define NULL 0
int main(void){
	char src[]="hello dynamic\n";
	int (*pStrlenFun)(char *str);
	void *phandle=NULL;
	char *perr=NULL;
	phandle=dlopen("./libstr.so",RTLD_LAZY);
	if(!phandle){
		printf("Failed Load Library!\n");
	}
	perr=dlerror();
	if(perr!=NULL){
		printf("%s\n",perr);
		return 0;}
	pStrlenFun=dlsym(phandle,"strlen");
	perr=dlerror();
	if(perr!=NULL){
		printf("%s\n",perr);
		return 0;}
	printf("string:%s",src);
	printf("the length is:%d\n",pStrlenFun(src));
	dlclose(phandle);
	return 0;
}

#include <stdio.h>
extern int strlen(char * string);
int main(void){
	char *str="hello world\n";
	int len=strlen(str);
	printf("the length is :%d\n",len);
	return 1;
}	

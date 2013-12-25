#include <iostream>
using namespace std;
char *p="ni hao";
void f(){
	char *b=p;
	printf("%s\n",b);
	strcpy(b,"ahao");
	printf("%s\n",b);
	return ;
}
int main(){
	char *a=p;
	strcpy(a,"haoa");
	printf("%s\n",p);
	f();
	int i;cin>>i;
	return 1;
}

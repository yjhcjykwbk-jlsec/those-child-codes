#include<stdio.h>
#include<string.h>
const int MAX=100;
char s[7];
int a[MAX],e,p,b,be,en,i;
void mul()
{
	int i,w=0;
	for(i=0;i<MAX;i++)
	{
		a[i]=a[i]*b+w;
		
		w=a[i]/10;
		a[i]=a[i]-w*10;
	}
}
int main()
{
	while (scanf("%s %d",s,&e)!=EOF)
	{
		memset(a,0,sizeof(a));
		b=0;			//Step 1 and Step 2
		for(i=0;i<strlen(s);i++)
			if (s[i]=='.') p=strlen(s)-i-1;
			else b=b*10+s[i]-'0';
		a[0]=1;			//Step 3
		for(i=0;i<e;i++)	
			mul();
		p*=e;			//Step 4
		for (be=MAX-1;a[be]==0&&be>=p-1;be--);
		for (en=0;a[en]==0&&en<p;en++);
		for (i=be;i>=p;i--) printf("%d",a[i]);
		if (en<p) printf(".");
		for (i=p-1;i>=en;i--) printf("%d",a[i]);
		printf("\n");
	}
	return 0;
}


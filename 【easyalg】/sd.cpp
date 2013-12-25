#include<iostream>
using namespace std;
void sort(int *a,int n)
{
int i,j,temp;
for(i=1;i<n;i++)
{
	temp=a[i];
	j=i-1;
	while(temp>a[j])
	{
	a[j+1]=a[j];
	j--;
	if(j<0)break;
	}
	a[j+1]=temp;
}
}
int f(int *a,int n)
{
  int i=0,j,k,num=0;
  sort(a,n);
  for(i=0;i<n;i++)
  {
    for(j=0;j<i;j++)
    {
     for(k=0;k<j;k++)
      {
        if(a[j]+a[k]==a[i])num++;
        if(a[j]+a[k]>a[i])break;
      }
    }
  }
return num;
}


int main()
{
int cases=0,i,j;
cin>>cases;
int res[100];
int a[102];
int n;
for(i=0;i<cases;i++)
{
cin>>n;
for(j=0;j<n-1;j++)
scanf("%d ",&a[j]);
scanf("%d",&a[j]);
sort(a,n);
res[i]=f(a,n);
}
for(i=0;i<cases;i++)printf("%d\n",res[i]);
return 1;
}



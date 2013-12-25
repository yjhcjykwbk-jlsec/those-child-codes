#include<iostream>
using namespace std;
int f(int *a,int x,int n)
{
a[1]=x;
int i=1;
int l=1,r=1;
while(i<n)
{
if(2*a[l]+1<3*a[r]+1)
{
a[++i]=2*a[l]+1;
l++;
}
else if(2*a[l]>3*a[r])
{
a[++i]=3*a[r]+1;
r++;
}
else 
{
a[++i]=2*a[l]+1;
l++;r++;
}
}
return a[n];
}
int main()
{
int a[10002];
int x,n;
while(scanf("%d %d",&x,&n)!=EOF) 
cout<<f(a,x,n)<<endl;
}

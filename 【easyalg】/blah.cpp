////blash数集
//怎么样获取第n个元素呢
#include<iostream>
using namespace std;
int f(int *a,int x,int n)
{
a[1]=x;
int i=1;
int l=1,r=1,p=1;
while(i<=n)
{
if(2*a[l]+1<3*a[r]+1)
{
a[++i]=2*a[l]+1;
l;
}
else
{
a[++i]=3*a[r]+1;
r=i;
}
}
return a[n];
}
int main()
{
int a[1000002];
int x,n;
cin>>x>>n;
cout<<f(a,x,n);
cin>>n;
}
 

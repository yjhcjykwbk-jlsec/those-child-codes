#include<iostream>
using namespace std;
struct stack
{
 int info[100];
 int p;
};
int f(stack &s,int *a,int n)
{
 int i=1,l,r,mid;
 s.info[++s.p]=a[0];
 for(;i<n;i++)
 {
 if(s.info[s.p]<a[i])
 {
    s.info[++s.p]=a[i];
 
 }
 else 
{
  r=s.p;
  l=0;
  mid=(l+r)/2;
  while(r-l>1)
  {
   if(s.info[mid]>a[i]) r=mid;
   else l=mid;
   mid=(l+r)/2;
  }
  if(s.info[l]>a[i]) s.info[l]=a[i];
  else s.info[r]=a[i];
 }
}
 return s.p+1;
}
int main()
{
 int a[10]={1,4,2,6,3,9,-1,45,0,7};
 stack s;
 s.p=-1;
 cout<<f(s,a,10);
 cin>>s.p;
return 1;
}

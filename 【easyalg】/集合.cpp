#include<iostream>
#include<math.h>
using namespace std;
int a[1000];
int set[1000];
int minIndex(int *set,int n)
{
    int res=0,i;
    for(i=0;i<n;i++) {if(set[i]<set[res])res=i;}
    return res;
}
int f(int *a,int n)
{
    int k=0,i,M=a[0];
    int temp=0,min=-1,maxnum=1;
    for(i=0;i<n;i++) if(a[i]>M)M=a[i];
    for(k=n;k>=1;k--)
    {
      for(i=0;i<k;i++) set[i]=0;
      for(i=0;i<n;i++)
      {
       int index=minIndex(set,k);
       set[index]+=a[i];
      }
      temp=0;
      for(i=0;i<k;i++)
      {
        temp+=(M>set[i])?(M-set[i]):(set[i]-M);
      }
      if(min==-1||min>temp){min=temp;maxnum=k;}
    }
    return maxnum;
}
int main()
{
    int n;
    cin>>n;
    int i=0;
    for(;i<n;i++) cin>>a[i];
    cout<<f(a,n);
    cin>>i;
    return 1;
}

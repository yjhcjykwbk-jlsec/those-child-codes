#include<iostream>
using namespace std;

  
int main()
{
  int n,m,i;
  cin>>n>>m;
  int a[10000];
  long sum=0;
  for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);sum+=a[i];
   }
  int average=sum/m;//最大长度
  if(average<1) {cout<<"0\n";return 1;}
  int num=0;
  for(i=0;i<n;i++)
  {
        num+=a[i]/average;
  }
  if(num==m) {cout<<average<<endl;return 1;}
  int l=1,r=average,mid;
  while(l<r-1)
 {
   mid=(l+r)/2;
   num=0;
   for(i=0;i<n;i++)
   {
        num+=a[i]/mid;
   }
   if(num>=m) {l=mid;}
   else r=mid;
 }
 num=0;
 for(i=0;i<n;i++)
 {
        num+=a[i]/r;
 }
 if(num>=m) cout<<r<<endl;
 else cout<<l<<endl;
 return 1;
} 
   
  
  

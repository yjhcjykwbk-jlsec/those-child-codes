#include<iostream>
using namespace std;
int a[101][101];
int l[101];
int n=100;
int m=20;//切成m段的最大长度
int f()
{
 int i,j,k,temp;
 for(i=0;i<=j;i++)
{
 a[0][i]=0;
}
for(i=1;i<n;i++)
{
 for(j=0;j<=m;j++)
 {
  if(l[i]<=a[i-1][j]) a[i][j]=a[i-1][j];
  else
  {
   a[i][j]=0;
   for(k=1;k<=j;k++)
    {
     temp=a[i-1][j-k];
     if(temp>l[i]/k) temp=l[i]/k;
     if(a[i][j]<temp) a[i][j]=temp;
    }
  }
  }
 }
}
int main()
{
 f();
 cout<<a[n][m];
 int i;
 cin>>i; 
 return 1;
}
   
   

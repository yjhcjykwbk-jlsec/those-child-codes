#include<iostream>
using namespace std;

int f(int *w,int num[][41],int n)
{
   int i,j;
   for(i=0;i<=40;i++)
   {
     num[1][i]=0;
   }
   num[1][0]=num[1][w[1]]=1;

   for(i=0;i<=40;i++)
   {
     for(j=2;j<=n;j++)
     {
       if(i>=w[j])
       num[j][i]=num[j-1][i]+num[j-1][i-w[j]];
       else num[j][i]=num[j-1][i];
     }
   }
   return num[n][40];
}
int main()
{
  int num[21][41];//记录到n的m物品种数
  int n;
  int w[21];
  cin>>n;
  int i;
  for(i=0;i<n;i++)
{
  cin>>w[i+1];
}
  cout<<f(w,num,n);
 return 1;
}

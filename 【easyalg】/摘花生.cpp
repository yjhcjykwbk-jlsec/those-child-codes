///Õª»¨Éú
#include<iostream>
using namespace std;
int step[2][2]={0,1,1,0};
int g(int a[][101],int num[][101],int n,int m)
{
      int i,j;
      int l,r;
      for(i=0;i<=n;i++)num[i][0]=0;
      for(i=0;i<=m;i++)num[0][i]=0;
      for(i=1;i<=n;i++)
      {
       for(j=1;j<=m;j++)
       {
         l=num[i][j-1]+a[i][j];
         r=num[i-1][j]+a[i][j];
         if(l>r) num[i][j]=l;
         else num[i][j]=r;
       }
      }
      return num[n][m];
}
         
int main()
{
    int cases,i,j,k,n,m;
    int a[101][101];
    int res[100];
    int num[101][101]; 
    cin>>cases ;
    for(i=0;i<cases;i++)
    {
     cin>>n>>m;
     for(j=1;j<=n;j++)
     {
      for(k=1;k<=m;k++)
      cin>>a[j][k];
     }
     res[i]=g(a,num,n,m);
    }
    for(i=0;i<cases;i++)
     cout<<res[i]<<endl;
     cin>>i;
     return 1;
    }

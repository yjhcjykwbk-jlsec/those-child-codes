#include<iostream>
using namespace std;
int step[4][2]={0,1,-1,0,0,-1,1,0};//////n.m
bool check(int arr[][102],int i,int j,int n,int m)
{
  int a=i-1;
  int b=j;
  if(a>=1)
  {if(arr[a][b]<arr[i][j]) return false;}
  a=i+1;
  if(a<=n)
  {if(arr[a][b]<arr[i][j]) return false;}
  a=i;b=j-1;
  if(b>=1)
  {if(arr[a][b]<arr[i][j]) return false;}
  b=j+1;
  if(b<=m)
  {if(arr[a][b]<arr[i][j]) return false;}
  return true;
}

void dp(int a[][102],int visited[][100],int i,int j,int n,int &maxnum)
{
   int k;
   int num=n+1;
   if(num>maxnum) {maxnum=num;}
   visited[i][j]=1;
   for(k=0;k<4;k++)
  {
    if(a[i+step[k][0]][j+step[k][1]]>a[i][j])
    {  
       if(0==visited[i+step[k][0]][j+step[k][1]])
       {
         dp(a,visited,i+step[k][0],j+step[k][1],num,maxnum);
         visited[i+step[k][0]][j+step[k][1]]=0;
        }
    }
  }
}

int getdp(int a[][102],int visited[][100],int n,int m)
{
  int num=0,maxnum=0,i,j,temp;
  for(i=1;i<=n;i++)
  {
    for(j=1;j<=m;j++)
   {
     if(check(a,i,j,n,m))
    {
        for(int c=0;c<n;c++)
        {
           for(int d=0;d<m;d++)
           {
               visited[c][d]=0;
           }
        }
       num=0;
       dp(a,visited,i,j,num,maxnum);
     }
   }
  }
  return maxnum;
}


         
  
int main()
{
    cout<<step[3][1];
  int a[102][102];
  int visited[100][100];
  int n,m;
  cin>>n>>m;
  int i,j;
  for(i=0;i<=n+1;i++) a[i][0]=a[i][m+1]=0;
  for(i=0;i<=m+1;i++) a[0][i]=a[n+1][i]=0;
  for(i=1;i<=n;i++)
     for(j=1;j<=m;j++)
        cin>>a[i][j];
        
  cout<<getdp(a,visited,n,m);
  cin>>i;
return 1;
}

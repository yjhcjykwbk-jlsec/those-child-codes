/////Î§Æå///
#include<iostream>
using namespace std;
int step[4][2]={0,1,1,0,0,-1,-1,0};
void f(int a[][22],int i,int j,int n)
{
if(a[i][j]==-1) return;
if(a[i][j]>n)a[i][j]=n;
int k=0;
for(k=0;k<4;k++)
{
    f(a,i+step[k][0],j+step[k][1],n+1);
}
}

int main()
{
char temp[20];
int a[22][22];
int n,m,x,y,dx,dy;
int res[100],i,j,k;

while(scanf("%d %d",&n,&m)!=EOF)
{
if(n==0&&m==0)break;
for(j=0;j<=m+1;j++)a[0][j]=a[n+1][j]=-1;
for(i=1;i<=n;i++)
{
scanf("%s",temp);
a[i][0]=a[i][m+1]=-1;
for(j=1;j<=m;j++) 
{
if(temp[j-1]=='@'){x=i;y=j;a[i][j]=0;}
if(temp[j-1]=='#')a[i][j]=-1;
if(temp[j-1]=='.')a[i][j]=404;
if(temp[j-1]=='*'){dx=i;dy=j;a[i][j]=404;}
}
}
f(a,x,y,0);
res[k]=a[dx][dy];
if(a[dx][dy]==404)res[k]=-1;
}
for(i=0;i<k;i++)printf("%d\n",res[i]);
cin>>i;
cin>>i; 
return 1;
} 

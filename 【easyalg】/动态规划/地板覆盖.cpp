#include<iostream>
#include<cmath> 
using namespace std;
int a[2048][2048];
long long b[2048][2];

void f(int a[][2048],int n)
{
int num,num1,i,j,p,pointer,have;
a[0][0]=(int)pow(2.0,n)-1;
a[0][1]=-1;
a[1][0]=a[0][0]-1;
a[1][1]=-1;
int b[11];
for(i=2;i<pow(2.0,n);i++)
{
num=i;
pointer=0;

for(j=0;j<n;j++)
{
b[j]=(num>>j)&1;
}

have=0;
for(p=0;p<n-1;p++)
{
if(b[p]==1&&b[p+1]==1){have=1;break;}
}

if(have==1)
 {
num=(int)pow(2.0,p)+(int)pow(2.0,(p+1));
for(j=0;a[i-num][j]!=-1;j++,pointer++){a[i][pointer]=a[i-num][j];}
for(j=0;a[i-num][j]!=-1;j++,pointer++){a[i][pointer]=a[i-num][j]-num;}
a[i][pointer]=-1;
if(p<n-2)
{ 
if(b[p+2]==1)  
{
num1=2*num;
for(j=0;a[i-num1][j]!=-1;j++,pointer++){a[i][pointer]=a[i-num1][j];}
a[i][pointer]=-1;}
}
}
else 
{
a[i][0]=(int)pow(2.0,n)-1-i;
a[i][1]=-1;
} 
}
}

long long  g(int a[][2048],long long b[][2],int m,int n)//nÎª¿í 
{
if(m<=0) return 0;
f(a,n);
int i=0,j,p,k,t;
int pp=(int)pow(2.0,n);

for(i=0;i<pp;i++)
{
b[i][0]=0;
}
p=0;
while(a[pp-1][p]!=-1) {b[a[pp-1][p]][0]=1;p++;}
for(i=1;i<m;i++)
{
  k=(i%2);t=1-k;
  for(j=0;j<pp;j++)
 {
   b[j][k]=0;
  }
  for(j=0;j<pp;j++)
 {
   p=0;
   while(a[j][p]!=-1){b[a[j][p]][k]+=b[j][t]; p++;}
  } 
} 
return b[pp-1][(m+1)%2];
}

int main()
{   
    int m,n;
    while(cin>>m>>n&&m>=0&&n>=0)
    {
    long long f=g(a,b,m,n);
    cout<<f<<endl;
    }
    return 1;
    
}

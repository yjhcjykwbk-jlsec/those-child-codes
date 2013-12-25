#include <iostream>
using namespace std;
///记录i j能否由k规则导出 
struct rule
{
       int l;
       int r;
};
bool f[100][100][26]={0};
///////f[i][j][k] 
void fun(int i,int j,int length[][100],rule rules[],int index[][20])
{
   int p=0;
   int a,b,x,y,t;
   for(int k=0;k<26;k++)
   {
    if(-1==index[k][0]) continue;
    p=0;
    while(-1!=index[k][p])
    {
       a=rules[index[k][p]].l;
       b=rules[index[k][p]].r;
       for(t=i;t<j;t++)
       {
          x=f[i][t][a];
          y=f[t+1][j][b];
          if(1==x&&1==y)
          {
            f[i][j][k]=1;
            break;
          }
       }
       p++;
     }
   }
    if(f[i][j]['S'-'A']){length[i][j]=1;return;} 
    else
    {
        length[i][j]=-1;
        for(t=i;t<j;t++)
       {
          x=length[i][t];
          y=length[t+1][j];
          if(0<x&&0<y)
          {
            if(x+y<length[i][j]||-1==length[i][j]) length[i][j]=x+y;
            if(2==length[i][j])return;
          }
       }       
    }
}
///初始化数组f 
void initialize(int n,int length[][100],rule rules[],int index[][20])//n为基因长度 
{
     int i,j;
     for(i=1;i<n;i++)
    {
       for(j=0;j<n;j++)
       { 
         if(j+i>=n)break;
         else
		 {
			 fun(j,j+i,length,rules,index);
		 }
       }
    }
}


int main()
{
    int length[100][100]={-1};
    rule rules[50];
    int index[26][20];//记录每个字母相应规则下标
    int n;
    cin>>n;
    int i,j,k;
	for(i=0;i<26;i++)
			index[i][0]=-1;; 
    char a,b,c;
	int s[26]={0};
	//初始化rules[]
    for(i=0;i<n;i++)       
    {
       cin>>a>>b>>c;
       rules[i].l=b-'A';
	   rules[i].r=c-'A';
	   index[a-'A'][s[a-'A']++]=i;
	   index[a-'A'][s[a-'A']]=-1;
    }
    //获取基因串
    char jean[101];
    cin>>jean;
    i=0;
    while(jean[i]!=0) 
	{
		f[i][i][jean[i]-'A']=1;
        if('S'==jean[i]) length[i][i]=1;
        i++;
	}
    n=i;
    initialize(n,length,rules,index);
    ////////////////求最短S(N)长度 
    cout<<length[0][n-1];
    return 1;
}

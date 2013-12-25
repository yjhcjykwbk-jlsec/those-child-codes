#include <iostream>
using namespace std;
///记录i j能否由k规则导出 
int f[100][100][26];
//////////////////////////////
//////////数据结构 
struct rule
{
       int l;
       int r;
       rule *next;
};
class list
{
      public:
       rule *first;
       rule *last;
       list()
    {
      first=last=NULL;
    }
};
void inlist(list &a,rule *b)
{
     if(a.last==NULL) a.first=a.last=b;
     else{a.last->next=b;
     a.last=b;
     }
}
void delist(list &a)
{
      rule * p=a.first;
      rule * q=a.first->next;
      while(p!=NULL)
      {
         delete p;
         p=q;
         if(q!=NULL) q=q->next;
      }
}
////////////////////////////////
///////初始化a[i][j][k] 
void fun(int i,int j,int k)//规则k能否推出i-j 
{
   
    if(i>=j||NULL==rules[k].first||2!=f[i][j][k]) return;
    rule *p=rules[k].first;
    int a,b,x,y;
    while(p!=NULL&&1!=f[i][j][k])
    {
       a=p->l;
       b=p->r;
       for(int t=i;t<j;t++)
       {
          x=f[i][t][a];
          y=f[t+1][j][b];
          if(1==x&&1==y)
          {
            f[i][j][k]=1;break;
          }
       }
       p=p->next;
    } 
    if(1!=f[i][j][k]) f[i][j][k]=0;
}
////////////////////////////////
///初始化数组a 
void initialize(int n)//n为基因长度 
{
     int i,j,k;
     for(i=1;i<n;i++)
    {
       for(j=0;j<n;j++)
       { 
         if(j+i>=n)break;
         for(k=0;k<26;k++) {fun(j,j+i,k);}
       }
    }
}
//////////////////////////// 
///s[n]最短长度 
int getNum(int i,int j)
{
    int k='S'-'A';
    int temp=f[i][j][k];
    int num=101;
    if(temp==1) return 1;
    else
    {
         int x,y;
         for(int t=i;t<j;t++)
       {
          x=getNum(i,t);
          y=getNum(t+1,j);
          if(x>0&&y>0)
          {
            if(x+y<num) num=x+y;
          }
          if(x==1&&y==1) return 2;
       } 
       if(num==101) return -1;
       else return num;
    }
}         
     
/////////////////////////// 
int main()
{
    int n;
    cin>>n;
    int i,j,k;
    char a,b,c;rule * temp;
    for(i=0;i<n;i++)       
    {
       cin>>a>>b>>c;
       temp=new rule();
       temp->next=NULL;
       temp->l=b-'A';
       temp->r=c-'A';
       inlist(rules[a-'A'],temp);
    }
    
    char jean[101];
    cin>>jean;
    i=0;
    while(jean[i]!=0) {f[i][i][jean[i]-'A']=1;i++;}
    n=i;
    for(i=0;i<n;i++)
    {
       for(j=i+1;j<n;j++)
       { 
         for(k=0;k<26;k++) {f[i][j][k]=2;}
       }
    }
    initialize(n);
    ////////////////求最短S(N)长度 
    cout<<getNum(0,n-1);       
    return 1;
}

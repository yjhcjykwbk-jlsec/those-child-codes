#include <iostream>
using namespace std;
int Max[50][50];//记录ij之间的最大值
int Min[50][50];
int  op[50];//操作数 
char cl[50];//运算符 
int n; 

//计算函数
//k对应运算符cl[k] 
int function(int aop,int k,int bop)
{ 
    if(cl[k]=='x')return (aop*bop);
    else return (aop+bop);
}
//初始化最大最小值数组 
int initialize()
{     
      int i,j,k; 
      int max=0,min=0,temp1,temp2; 
      int a,b; 
      for(i=0;i<n;i++) 
      {
          Max[i][0]=Min[i][0]=op[i]; 
          Max[i][1]=Min[i][1]=function(op[i],(i+1)%n,op[(i+1)%n]);//计算点i到点i+1边的值
      }
      for(i=2;i<n;i++)//点j到 j+i之间最大值最小值 
      {
        for(j=0;j<n;j++)
        {
           for(k=1;k<=i;k++) //i种切分方式 
           {
             temp1=function(Max[j][k-1],(j+k)%n,Max[(j+k)%n][i-k]);//点j--点j+k-1__点j+k--点j+i 
             temp2=function(Min[j][k-1],(j+k)%n,Min[(j+k)%n][i-k]);
             //更新最大最小值 
             if(k==1) {max=((temp1>temp2)?temp1:temp2);min=((temp2>temp1)?temp1:temp2);}
             else {
                  if(temp1>temp2) {a=temp1;b=temp2;} 
                  else            {a=temp2;b=temp1;}
                  if(max<a) max=a;
                  if(min>b) min=b;
                  }
           }
           Max[j][i]=max;Min[j][i]=min;
         }
      }
}
                
                                      
int main()
{
    cin>>n;
    int i;
    for(i=0;i<n;i++)
    {
       cin>>cl[i]>>op[i];
    }
    initialize();
    int temp=Max[1][n-1];
    int j=-1;
    int a[30];
    for(i=0;i<n;i++)
    {//Max[i][n-1]对应剪掉边i+1后的段（点i到点i-1) 
       if(Max[i][n-1]>temp)
       {
           temp=Max[i][n-1];
           j=0;
           a[j]=i+1;//点下标加1就是边的编号 
       }
       else if(Max[i][n-1]==temp)
       {
           a[++j]=i+1;
       }
    }
    cout<<temp<<endl;
    for(i=0;i<j;i++)
    {
       cout<<a[i]<<" ";
    } 
    cout<<a[j];
    return 1;
}
     
       
    

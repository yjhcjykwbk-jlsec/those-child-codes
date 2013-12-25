#include <iostream>
using namespace std;
char a[8][8];
int used[8]={0};
int n,num;//num为子数目 
int number=0;//排放方法数 
void f(int m,int k)//从第m行开始排第k颗子 。
{   
    if(k>num){ number++;return;}
    int i,j;
    for(j=m;j<n-(num-k);j++)
    { 
        for(i=0;i<n;i++)
        {
            if(a[j][i]=='#'&&0==used[i])
            {
               used[i]=1;
               f(j+1,k+1);
               used[i]=0;
            }
        }
    }
} 
int main()
{
    int i;
    while(cin>>n>>num&&(n!=-1||num!=-1))
    {
      for(i=0;i<n;i++)
      { 
          scanf("%s",a[i]);
      }
      number=0;
      f(0,1);//从0行开始放第一颗子
      printf("%d\n",number);
    }
    return 1; 
    
} 

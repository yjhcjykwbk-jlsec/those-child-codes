#include<iostream>//
//#include <rand.h>
#include <stdlib.h>
using namespace std; 
int arr[300];
int heap[300];

int f(int num)
{
    int i=0;
    for(i=0;i<num;i++)
    {
      arr[i]=heap[i]=rand()%2+1;
      }
    }
int g(int num)
{
    ///
    int i=0,j,k,temp,Max,p, res=0;
    for(k=1;k<num;k++)
    {
    Max=heap[0];
    for(i=0;i<num-k;i++)
    {
       temp=heap[i]+heap[i+1];
       if(temp>Max){p=i;Max=temp;}
    }
    res+=Max;
    heap[p]=Max;
    for(j=p+1;j<=num-k;j++){heap[j]=heap[j+1];}
   }
   return res;
}
int h(int tex[][300],int max[][300],int num)
{
    int i,j,k;int a,b;
    tex[0][0]=arr[0];
    for(i=1;i<num;i++){tex[0][i]=tex[0][i-1]+arr[i];}
    for(i=1;i<num;i++)
    {
      for(j=0;j<num;j++)
        tex[i][j]=tex[i-1][j]-arr[i-1];
    }
    for(i=0;i<num;i++) max[i][i]=0;
    for(i=1;i<num;i++) 
    {
      for(j=0;j<num;j++)
      {
         if(j+i>=num)break;
         max[j][j+i]=0;
         for(k=j;k<i+j;k++)
         {
            a=max[j][k];
            b=max[k+1][j+i];
            if(a+b>max[j][j+i])max[j][j+i]=a+b;
         }
         max[j][j+i]+=tex[j][j+i];
      }
    }
    return  max[0][num-1];
}       
            
int main()
{
    int max[300][300];
    int tex[300][300];
    int num;int a,b;
    int j;
    for(j=1;j<299;j++)
    {
                      num=j;
    f(num);
    a=g(num);
    b=h(tex,max,num);
    if(a==b) printf("r\n");
    else printf("wa\n");
    }
    int i;cin>>i;
}
       

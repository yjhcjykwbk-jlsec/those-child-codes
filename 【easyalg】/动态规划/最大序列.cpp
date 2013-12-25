#include <iostream>
using namespace std;
//int  num[10]={-1,2,-4,5,6,-7,1,3,-7,9};
int f(int *num,int n,int max[][2])
{
    int input=0;
    int Max=0;
    int a;
    for(a=0;a<n;a++)//从左开始0-a最大值 
    {
      input+=num[a];
      if(input>Max){max[a][0]=input;Max=input;}
      else max[a][0]=Max;
      if(input<0) input=0;
    }
    input=Max=0; 
    for(a=n-1;a>=0;a--)//a-n-1最大值 
    {
       input+=num[a];
       if(input>Max){max[a][1]=input;Max=input;}
       else max[a][1]=Max;
       if(input<0) input=0;
    }
    Max=0;
    for(a=0;a<n-1;a++)
    {
       if(max[a][0]+max[a+1][1]>Max){Max=max[a][0]+max[a+1][1];}
    }
    return Max;
}
    


int main()
{
  int num[50000];
  int max[50000][2];
  int res[31]; 
  int cases,n;
  cin>>cases;
  int i=0,j;
  for(i=0;i<cases;i++)
  {
    cin>>n;
    for(j=0;j<n;j++) cin>>num[j];
    res[i]=f(num,n,max);
  }
  for(i=0;i<cases;i++)cout<<res[i]<<endl; 
  return 1;
}

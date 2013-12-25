#include <iostream>
using namespace std;
int f(int *num,int n,int max[][2])
{
    int input=0;
    int Max=num[0];
    int a;
    for(a=0;a<n;a++)//从左开始0-a最大值 
    {
      input+=num[a];
      if(input>Max){Max=input;}
      max[a][0]=Max;
      if(input<0) input=0;
    }
    input=0;
    Max=num[n-1]; 
    for(a=n-1;a>=0;a--)//a-n-1最大值 
    {
       input+=num[a];
       if(input>Max){Max=input;}
       max[a][1]=Max;
       if(input<0) input=0;
    }
    
    Max=max[0][0]+max[1][1];
    for(a=1;a<n-1;a++)
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
    for(j=0;j<n-1;j++) scanf("%d ",&num[j]);
    scanf("%d",&num[j]);
    res[i]=f(num,n,max);
    //cout<<res[i]<<endl;
  }
  for(i=0;i<cases;i++)printf("%d\n",res[i]); 
  return 1;
}

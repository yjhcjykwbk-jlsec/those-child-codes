////登山
#include<iostream>
using namespace std;
int f(int num[][2],int height[],int n)
{
    int i=0,j;
    for(i=0;i<n;i++) num[i][0]=1; 
    for(i=1;i<n;i++)
    {
      for(j=0;j<i;j++)
      {
        if(height[j]<height[i]) 
        {
          if(num[j][0]+1>num[i][0]) num[i][0]=num[j][0]+1;
        }
      }
    }
    for(i=0;i<n;i++) num[i][1]=0;//i已经浏览过。现在从这里开始下山 
    for(i=n-1;i>=0;i--)//从i开始下山。注意a[i]==a[i-1]的情况 
    {
      for(j=i+1;j<n;j++)
      {
        if(height[j]<height[i]) 
        {
          if(num[j][1]+1>num[i][1]) num[i][1]=num[j][1]+1;
        }
      }
    }
    int max=0;
    for(i=0;i<n;i++){if(num[i][0]+num[i][1]>max)max=num[i][0]+num[i][1];}
    return max;
}
    
    
    
int main()
{
    int  num[1000][2];
    int height[1000];
    int n;
    cin>>n;
    int i;
    for(i=0;i<n;i++) cin>>height[i];
    cout<<f(num,height,n);
    cin>>i;//////////////////////
    return 1;
}
    
         

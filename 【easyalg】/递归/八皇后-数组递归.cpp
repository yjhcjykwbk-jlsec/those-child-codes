#include <iostream>
#include <math.h>
using namespace std;
void f(int *a,int n,int k,int &num)
{
     int have =0;
     if(k==n-1) num=0;  
     for(int i=0;i<n;i++)
     {
             a[k]=i;
             have=0;
             for(int j=n-1;j>k;j--)
             {
                     if((a[j]-a[k]==j-k)||(a[k]-a[j]==j-k)||a[j]==a[k]) {have=1;break;}
             }
             if(have!=1) 
             {
                  if(k==0) 
                  {
                           num++;
                           for(int m=0;m<n;m++)cout<<m<<" "<<a[m]<<endl;
                           continue;
                           }
                  else f(a,n,k-1,num);
             }
     }
}
int main()
{
    int num=0;
    int a[8]={0};
    f(a,8,7,num);
    cout<<num;
    cin>>a[0];
}

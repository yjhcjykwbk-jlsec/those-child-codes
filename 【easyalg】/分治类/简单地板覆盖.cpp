//
#include<iostream>
using namespace std;
int a[40];
void f(int *a,int n)
{
     int m;
    a[0]=a[1]==0;a[2]=3;
    for(int i=3;i<n;i+=1)
   {
                     if(i%2==1)a[n]=0;
                     else{
                          m=i-4;
                          a[i]=a[i-2]*3;
                          while(m>0)
                          {a[i]+=a[m]*2;m-=2;}
                          a[i]+=2;//a[0]
                     }
   }
}
int main()
{
    f(a,31);
    int n;
    while(cin>>n&&n>=0)cout<<a[n]<<endl;
}

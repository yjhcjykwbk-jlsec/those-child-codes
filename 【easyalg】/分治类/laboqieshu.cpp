////
#include<iostream>
using namespace std;
int multiply(int c[][2],int a[][2],int temp[][2],int m)
{
    int i=0,j,k,s;
    for(i=0;i<2;i++)
    {
                    for(j=0;j<2;j++)
                    {
                                    s=0;
                                    for(k=0;k<2;k++)
                                    {s+=c[i][k]*a[k][j];s=s%m;}
                                    temp[i][j]=s;
                    }
    }
     for(i=0;i<2;i++)
    {
                    for(j=0;j<2;j++)
                    {
                                    c[i][j]=temp[i][j];
                    }
    }
}
    
int f(int a[][2],int n)
{
    if(n==0) return 0;
    int b[40]={0};
    int t=n,pointer=-1;
    while(t>1)
    {
            b[++pointer]=t;
            t=t/2;
    }
    int i,temp[2][2],c[2][2],m=10000;
    for(i=0;i<4;i++){temp[i/2][i%2]=c[i/2][i%2]=a[i/2][i%2];}
    for(i=pointer;i>=0;i--)
    {
        multiply(c,c,temp,m);
        if(b[i]%2==1)   
        multiply(c,a,temp,m);
    }
    return c[0][1];
}
    
int main()
{
    int n;
    int a[2][2]={0,1,1,1};
    while(cin>>n&&n!=-1)
    {
                        cout<<f(a,n)<<endl;
    }
}
                        
                        

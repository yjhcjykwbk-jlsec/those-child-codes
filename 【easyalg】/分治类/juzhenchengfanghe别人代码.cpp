#include<iostream>
using namespace std;
//b=b*a             
void multiply(int b[][31],int a[][31],int temp[][31],int n,int m)     
{
     int i,j,s,k;
     for(i=0;i<n;i++)
                     for(j=0;j<n;j++)
                         {
                                      s=0;
                                      for(k=0;k<n;k++)
                                      { s+=(b[i][k])*(a[k][j])%m;s=s%m;}   
                                      temp[i][j]=s%m;
                         }
      for(i=0;i<n;i++)
                     for(j=0;j<n;j++)
                           {b[i][j]=temp[i][j]; }
}
//b=b+a  
void add(int a[][31],int b[][31],int n,int m)
{     
      int i,j;
      for(i=0;i<n;i++)
                     for(j=0;j<n;j++)
                           {b[i][j]+=a[i][j]; b[i][j]=(b[i][j])%m;}
}    
void f(int a[][31],int c[][31],int n,int m,int K)
{
    int k[100],i,j,p;
    int pointer=0;
    int t=K/2;
    k[0]=K;
    int b[31][31];  
    int d[31][31]; 
    int temp[31][31]; 
    for(i=0;i<n;i++)
      for(j=0;j<n;j++)
        d[i][j]=c[i][j]=b[i][j]=a[i][j];
      
    while(t>=1)
    {
        k[++pointer]=t;
        t=t/2;
    }
    for(i=pointer;i>0;i--)      
    {
        if(k[i]>1)
        {
                  multiply(b,b,temp,n,m);//b=b*b
                  if(k[i]%2==1) multiply(b,a,temp,n,m);
        }
        //c1=c0+c0*b
        for(p=0;p<n;p++)
                     for(j=0;j<n;j++)
                           {d[p][j]=c[p][j];}//d=c0
        multiply(c,b,temp,n,m);//c2=c0*b
        add(d,c,n,m);//c1=c2+d
        if(k[i-1]%2!=0)
        {//c1'=c1*a+a
             multiply(c,a,temp,n,m);
             add(a,c,n,m);  
        }
        //cout<<"S"<<k[i-1]<<":"<<endl;
    } 
}
int main()
{
    int n,k,m;
    cin>>n>>k>>m;
    int a[31][31],b[31][31];
    int i,j;
    for(i=0;i<n;i++)
                    for(j=0;j<n;j++)
                                    cin>>a[i][j];
    f(a,b,n,m,k);
    for(i=0;i<n;i++)
    {                for(j=0;j<n-1;j++)
                    {cout<<b[i][j]<<" ";}
                    cout<<b[i][j]<<endl;
    }
}
    
    

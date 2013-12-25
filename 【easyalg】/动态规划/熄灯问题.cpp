#include<iostream>
using namespace std;
bool f(int a[][6],int temp[][6])
{
    int i=0,j=0;
    for(i=1;i<5;i++)
    {
      for(j=0;j<6;j++)
      {
        temp[i][j]=(temp[i-1][j]+a[i][j])%2;
        if(j>0)temp[i][j]=(temp[i][j]+temp[i][j-1])%2;
      }
    }
    for(j=0;j<6;j++){if((temp[4][j]+a[5][j])%2!=0)return false;}
    return true;
}
    


int main()
{
    int a[10][5][6];
    int temp[5][6];
    int n,i,j,k,p;
    cin>>n;
    for(i=0;i<n;i++)
    {
      for(j=0;j<30;j++)
        cin>>a[i][j/6][j%6];
    }
    for(i=0;i<n;i++)
    {
       for(j=0;j<30;j++)
        temp[j/6][j%6]=0;
       for(j=0;j<64;j++)
       {
         for(k=5;k>=0;k--)
         { 
           temp[0][k]=(j>>k)&1;
         }
         if(f(a[i],temp)){for(p=0;p<30;p++){a[i][p/6][p%6]=temp[p/6][p%6];}break;}
       }
    } 
    for(i=0;i<n;i++)
    {
      for(j=0;j<5;j++)
       { for(k=0;k<6;k++)
         { printf("%d ",a[i][j][k]);}
        printf("\n");}
    }
    cin>>i;
    return 1;
}   
                   
         
    

#include <iostream>
using namespace std;
int a[20][20];
int f()
{
    int i=0;
    for(i=2;i<20;i+=2)
    {
      a[1][i]=a[i][1]=1;
    }
    for(i=1;i<20;i+=2)
    {
      a[1][i]=a[i][1]=0;
    }
    for(i=1;i<n;i++)
    {
       for(j=1;j<m;j++)
       {
         
    

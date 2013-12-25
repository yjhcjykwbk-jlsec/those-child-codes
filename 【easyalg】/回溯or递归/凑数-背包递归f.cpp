#include <iostream>
using namespace std;
int f(int *a,int *b,int n,int k)
{
    if(k==0) return 1;
    if(k<0||n<0) return 0;
    if(f(a,b,n-1,k-a[n]))  { b[n]=1;return 1;}
    if(f(a,b,n-1,k)) {return 1;}
    return 0;
}
    
int main()
{
    int a[10]={1,2,6,7,11,13,20,25};
    int b[10]={0};
    f(a,b,7,37);
    for(int i=0;i<8;i++)
    {
            if(b[i])cout<<a[i]<<" ";
    }
    cin>>a[1];
}
    

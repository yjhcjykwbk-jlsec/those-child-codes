#include <iostream>
using namespace std;
int kt(int n,int k);
int f(int n,int k)
{
    if(k<n)return f(k,k);
    int m=0;
    for(int i= n;i>=1;i--)
    {
            m+=(kt(i,k));
    }
    return m;
}
int kt(int i,int n)
{
    if(n<i)return 0;
    if(i==1||i==n)return 1;
    return f(i,n-i);
}
int main()
{

    int n=3;int k=1;
  while(cin>>n>>k)
  {
                  if(n<=0)break;
                    cout<<f(n,k)<<endl;
   }
    
} 

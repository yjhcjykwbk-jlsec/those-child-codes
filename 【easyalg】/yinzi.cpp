///因子问题
#include<iostream>
using namespace std;
int f(int N,int M)
{
    int i=1;
    while(M>=2*i)
     { 
       if(N%i==0&&N%(M-i)==0) break;
       i++;
     }
     if(N%i!=0||N%(M-i)!=0) return -1;
     else return i;
}
int main()
{
    int cases;
    cin>>cases;
    int i,j,N,M;
    int res[100];
    for(i=0;i<cases;i++)
    {
            cin>>N>>M;
            res[i]=f(N,M);
    }
    for(i=0;i<cases;i++)
    {
                        cout<<res[i]<<endl;
                        }
    return 1;
}
       

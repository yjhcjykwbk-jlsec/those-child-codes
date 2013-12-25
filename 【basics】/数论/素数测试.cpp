//数论 素数测试
#include<algorithm>
#include<iostream>
#include<fstream>
using namespace std;
fstream out("out.txt",ios::out);
int modular_exp(int a,int n,int b)
{
    int x=n;
    int res=1;
    while(x>0)
    {
            res=(res*res)%b;
            if((x%2)==1) res=(res*a)%b;
            x=(x/2);
    }
    return res;
}
bool is_sushu(int n)
{
     int t;
     for(int i=3;i<5;i+=2)//关于i的选取犹存疑虑 
     {
             t=modular_exp(i,n-1,n);
             if(t!=1 ){return 0;}//out<<i<<" "<<n-1<<"  "<<t<<endl;
     }
     return true;
}
int main()
{
    for(int i=3;i<10000000;i+=2)
      if(is_sushu(i)) out<<i<<endl;
}
       

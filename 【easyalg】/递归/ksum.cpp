#include <iostream>
using namespace std;
double f(double *num,int n,int &left,int &right)
{
    double input=0;
    double Max=num[0];
    int a;
    int l=0;
    left=right=0;
    for(a=0;a<n;a++)
    {
      input+=num[a];
      if(input>Max){Max=input;left=l;right=a;}
      if(input<0) {input=0;l=a+1;}
    }
    return Max;
}
    


int main()
{
    int n;
    double a[100000];
    cin>>n;
    int i;
    for(i=0;i<n;i++){cin>>a[i];}
    int left,right;
    double sum=f(a,n,left,right);
    cout<<sum<<endl;
    cout<<left<<endl;
    cout<<right<<endl;
}

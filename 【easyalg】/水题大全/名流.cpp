#include<iostream>
using namespace std; 
 
int a[10000][10000];
int b[10000];
int main()
{
    int l,r,i,j;
    int n;
    cin>>n;
    for(i=0;i<n;i++)
                    for(j=0;j<n;j++)
                                    a[i][j]=0;
    memset(b,0,n);
    while(cin>>l>>r&&(l!=0||r!=0)){a[l][r]=1;b[l]=1;}
    for(i=0;i<n;i++)
    {
                    if(b[i]==1) continue;
                    for(j=0;j<n;j++)
                    {
                       if(j==i)continue;
                       if(a[j][i]==0) {break;}
                    }
                    if(j>=n) break;
    }
    if(i>=n) cout<<"NO FOUND"<<endl;
    else cout<<i<<endl;  
}

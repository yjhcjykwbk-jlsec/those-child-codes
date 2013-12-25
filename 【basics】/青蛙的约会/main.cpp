#include<iostream>
using namespace std;
int a(int x,int y,int m,int n,int cir)
{
int l;
int c;
if(x==y)  return 0;
if(m>n)
{
c=m-n;
if(x<y) l=cir-(x-y);
else l=x-y;
}
else 
{
c=n-m;
if(x<y) l=cir+x-y;
else l=x-y;
}
int t=(c-(l%c))%c;
if(t==0) return (l/c);

if(cir%c==0) return 0;
else
{
int temp=(cir%c);
int xx=temp;
for(int i=1;i<=c;i++)
{
if(temp==t) return ((i*cir+l)/c);
else temp=(xx+temp)%c;
}

return 0;
}
}


int main()
{
    int x,y,m,n,c;
    cin>>x>>y>>m>>n>>c;
    int vv=a(x,y,m,n,c);
    if(vv==0) printf("Impossible");
    else printf("%d",vv);
    return 1;
}
 

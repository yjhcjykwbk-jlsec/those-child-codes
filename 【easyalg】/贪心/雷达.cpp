#include<iostream>
#include<cmath>
using namespace std;
struct dt
{
       int x,y;
};
struct bt
{
       double left,right;
};
int f(dt *a,bt *b,int n,int r)
{
    int i,x,y;
    double dx;
    for(i=0;i<n;i++)
    {
       x=a[i].x;
       y=(int)fabs(a[i].y);
       if(y>r) return 0;
       dx=pow(r*r-y*y,0.5); 
       b[i].left=x-dx;
       b[i].right=x+dx;
    }
    return 1;
}
bool compare(bt &a,bt &b)
{
     if(a.left<b.left)return true;
     if(a.left>b.left) return false;
     if(a.right<b.right) return true;
     else return false;
}
void sort(bt *b,int n)
{
     int i=0,j;
     bt temp;
     for(i=0;i<n-1;i++)
     {
        for(j=n-1;j>i;j--)
        {
           if(compare(b[j],b[j-1]))  //<
           { 
             temp=b[j];b[j]=b[j-1];b[j-1]=temp;
           }
        }
     }
}
int g(dt *a,int n,int r)
{
    bt b[1000];
    int res=f(a,b,n,r);
    if(res==0) return -1;
    sort(b,n);
    double last=b[0].right;
    int sum=1;
    int i;
    for(i=1;i<n;i++)
    {
      if(b[i].left>last) {sum++;last=b[i].right;}
      if(b[i].right<last) last=b[i].right;
    }
    return sum;
}
int main()
{
    int n,d,i;
    dt a[1000];
    int res[1000];
    int Case=-1;
    while(scanf("%d %d",&n,&d)&&(n!=0||d!=0))
    {
       for(i=0;i<n;i++) 
       { 
                        scanf("%d %d",&a[i].x,&a[i].y);
       }
       res[++Case]=g(a,n,d);
    }
    for(i=0;i<=Case;i++) printf("Case %d: %d\n",i+1,res[i]);
}
    

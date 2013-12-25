//zuixiaofugai
#include <iostream>
using namespace std;
struct DT
{
       int l,r;
};
void swap(DT *a,int i,int j)
{
     DT temp=a[i];
     a[i]=a[j];
     a[j]=temp;
}
bool compare(DT &a,DT &b)
{
     if(a.l<b.l)return true;
     if(a.l>b.l)return false;
     if(a.r>b.r)return true;
     else return false;
}
void sort(DT *dt,int left,int right)
{
    if(left>=right)return ;
    int t=right;
    int l=left,r=right-1;
    while(l<=r)
    {
               while(compare(dt[l],dt[t])) l++;
               while(r>left&&!compare(dt[r],dt[t])) r--;
               if(l<r) swap(dt,l,r);
               else break;
               }
    swap(dt,l,t);
    sort(dt,left,l-1);
    sort(dt,l+1,right);           
}                              
int f(DT *dt,int n,int M)
{
    sort(dt,0,n-1);
    int i,left,right=0,have=0,last=0,pointer=0;//记录上次最右界限 
    //for(i=0;i<n;i++)cout<<dt[i].l<<" "<<dt[i].r<<endl;
    for(i=0;i<n;i++)
    { 
       if(dt[i].l>last)
       {
                      ++pointer;
                      last=right;
                      if(last>=M) {have=1;break;}
                      if(dt[i].l>last) return 0;
                      right=dt[i].r;                                     
       }
       if(dt[i].r>right){right=dt[i].r;}
    }
    if(right<M) return 0;
    if(!have) ++pointer;
    return pointer;
}
int main()
{
    int n=0,i=0,M;
    DT a[100000];
    cin>>M;
    while(cin>>a[i].l>>a[i].r&&(a[i].l!=0||a[i].r!=0)){i++,n++;}
    int res=f(a,n,M);
    if(res==0) cout<<"No solution"<<endl;
    else
    {cout<<res<<endl;}
    cin>>i;
}
        

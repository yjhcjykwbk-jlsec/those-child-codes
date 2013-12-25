#include<iostream>
using namespace std;
struct dt{
int x1;int x2;int h;
};
bool  compare(dt &t1,dt &t2)//< true >=false
{
 if(t1.h<t2.h) return false;//t1>t2 
 if(t1.h>t2.h) return true;
 else
 {
 if(t1.x1<t2.x1) return true;
 else return false;
 }
}
void swap(dt *a,int i,int j)
{
     dt temp;
     temp.x1=a[i].x1,temp.x2=a[i].x2,temp.h=a[i].h;
     a[i].x1=a[j].x1,a[i].x2=a[j].x2,a[i].h=a[j].h;
     a[j].x1=temp.x1,a[j].x2=temp.x2,a[j].h=temp.h;
}
void sort(dt *a,int l,int r)
{
 if(l>=r)return;
 int s=r;
 int left=l,right=r-1;
 while(left<=right)
 {
  while(compare(a[left],a[s])) left++;
  while(right>=l&&!compare(a[right],a[s]))right--;
  if(left<right) swap(a,left,right);
  else break;
 }
 swap(a,s,left);
 sort(a,l,left-1);
 sort(a,left+1,r);
}
int f(dt *a,int t[][2],int max,int n,int x,int y)//´ÓxyÏÂÂä
{
 int i=0,j;
 int temp=0;
 for(i=0;i<=n;i++)
 {
  if(a[i].x1==x&&a[i].x2==x&&a[i].h==y){ t[i][0]=t[i][1]=0;}
  else t[i][0]=t[i][1]=9999;
 }
 for(i=0;i<n;i++)
 {
  if(t[i][0]==9999) continue;
  for(j=i+1;j<=n;j++)
  {
    if(a[j].x1<=a[i].x1&&a[j].x2>=a[i].x1||j==n) 
    {
     if(a[i].h-a[j].h>max) break;
     else  
     {
        if(j==n) temp=t[i][0]+a[i].h;
  	    else temp=t[i][0]+a[i].h-a[j].h+a[i].x1-a[j].x1;
        if(t[j][0]>temp) t[j][0]=temp;
        temp=t[i][0]+a[i].h-a[j].h+a[j].x2-a[i].x1;
        if(t[j][1]>temp) t[j][1]=temp;
     }
     break;
    }
  }
  for(j=i+1;j<=n;j++)
  {
    if(a[j].x1<=a[i].x2&&a[j].x2>=a[i].x2||j==n) 
    {
     if(a[i].h-a[j].h>max) break;
     else  
     {  if(j==n) temp=t[i][1]+a[i].h;
        else temp=t[i][1]+(a[i].h-a[j].h)+a[i].x2-a[j].x1;
        if(t[j][0]>temp) t[j][0]=temp;
  	    temp=t[i][1]+(a[i].h-a[j].h)+a[j].x2-a[i].x2;
        if(t[j][1]>temp) t[j][1]=temp;
     }
     break;
    }
  }
 }
 return t[n][0];
}
int main()
{
 int i,j,n,max,x,y;
 int res;
 int t[1002][2];
 dt a[1002];

 cin>>n>>x>>y>>max;
 a[0].x1=a[0].x2=x;a[0].h=y;
 for(i=1;i<=n;i++)
 {
  cin>>a[i].x1>>a[i].x2>>a[i].h;
 }
 sort(a,0,n);a[n+1].h=0;
 res=f(a,t,max,n+1,x,y);
 cout<<res<<endl;
 return 1;
}

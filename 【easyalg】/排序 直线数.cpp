#include<iostream>
#include<stdlib.h>
using namespace std;
struct pos
{
  int x,y;
};
void swap(double *a,int l,int r)
{
 double temp=a[l];
 a[l]=a[r];
 a[r]=temp;
}

int partition(double *a,int l,int r)
{
  int s=r;
  int left=l,right=r-1;
  while(left<=right)
 {
    while(a[left]<a[r]) {left++;}
    while(right>=l&&a[right]>=a[r]){right--;}
    if(left<right) swap(a,left,right);
    else break;
  }
 swap(a,r,left);
 return left;
}
void sort(double *a,int l,int r)
{
  if(l>=r)return;
  int qs=partition(a,l,r);
  sort(a,l,qs-1);
  sort(a,qs+1,r);
}
int main()
{
    pos s[701];
    int n;
    cin>>n;
    int i,j,k;
    for(i=0;i<n;i++)scanf("%d %d",&s[i].x,&s[i].y);
    scanf("%d",&i);
    double a[701];
    int max=2,num;
    double temp;
    for(i=0;i<n-1&&i<n-max-1;i++)
   {
     for(j=i+1;j<n;j++)
    {
      if(s[j].x==s[i].x) a[j-i-1]=999999;
      else
      a[j-i-1]=(double)(s[j].y-s[i].y)/(double)(s[j].x-s[i].x);
    }
    sort(a,0,j-i-2);
    temp=a[0],num=2;
    for(k=1;k<=j-i-2;k++)
    {               
      if(a[k]==temp||(a[k]-temp<0.00001&&temp-a[k]<0.00001)) {num+=1;}
      else 
      {
      if(num>max)max=num;
      num=2;temp=a[k];
      }
    }
    if(num>max)max=num;
  }
  cout<<max;
  return 1;
} 
  

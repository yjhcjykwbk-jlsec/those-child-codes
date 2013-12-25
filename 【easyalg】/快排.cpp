#include<iostream>
#include<stdlib.h>
using namespace std;
class pos{
      public:
             int x,y;
             pos(){x=0;y=0;}
             void operator =(pos &s){x=s.x,y=s.y;}
             bool operator <(pos&s){if(x<s.x||(x==s.x&&y>s.y))return true;return false;}
             bool operator >(pos&s){if(x<s.x||(x==s.x&&y>s.y))return false;return true;}
      };

void swap(pos *a,int l,int r)
{
 pos temp=a[l];
 a[l]=a[r];
 a[r]=temp;
}

int partition(pos *a,int l,int r)
{
  int s=rand()%(r-l+1)+l;
  swap(a,s,r);
  int left=l,right=r;
  while(left<=right)
 {
    while(a[left]<a[r]) {left++;}
    while(a[right]>a[r]&&right>=l){right--;}
    if(left<right) swap(a,left,right);
  }
 swap(a,r,left);
 return left;
}
void sort(pos *a,int l,int r)
{
  if(l>=r)return;
  int qs=partition(a,l,r);
  sort(a,l,qs-1);
  sort(a,qs+1,r);
}
int main()
{
    pos a[50000];
    int n;
    cin>>n;
    int i,j=-1;
    for(i=0;i<n;i++)scanf("%d %d",&a[i].x,&a[i].y);
    sort(a,0,n-1);
    
    int left=a[0].x,rmost=a[0].y;
    pos b[1000];//¼ÇÂ¼±ÕÇø¼ä 
    for(i=1;i<n;i++)
    {
      if(a[i].x>rmost) {b[++j].x=left;b[j].y=rmost;left=a[i].x;}
      if(a[i].y>rmost) 
      {
          rmost=a[i].y;
      }
    }
    b[++j].x=left;b[j].y=rmost;
    
    for(i=0;i<=j;i++)
     cout<<b[i].x<<" "<<b[i].y<<endl;
    return 1;
} 
  

#include <iostream>
#include <string.h>
using namespace std;
void merge(char a[][20],char temp[][20],int l,int mid,int r)
{
  int left=l,right=mid+1,middle=mid; 
  int i=l;
  while(left<=mid&&right<=r)
  {
   if(-1==strcmp(a[left],a[right]))
     strcpy(temp[i++],a[left++]);
   else strcpy(temp[i++],a[right++]);
  }
  if(left>mid) 
   while(right<=r) {strcpy(temp[i++],a[right++]);}
  else while(left<=mid) {strcpy(temp[i++],a[left++]);}
  for(i=l;i<=r;i++) strcpy(a[i],temp[i]);
}
void sort(char a[][20],int l,int r)
{
  char temp[256][20];
  if(l==r)return;
  int mid=(l+r)/2;
  sort(a,l,mid);
  sort(a,mid+1,r);
  merge(a,temp,l,mid,r);
}
int f(char a[][20],int n)
{
 sort(a,0,n-1);
 int i=0,j;
 for(i=0;i<n-1;i++)
 {
  for(j=0;a[i][j]!=0&&a[i+1][j]!=0;j++)
  {
      if(a[i][j]!=a[i+1][j]) a[i][j+1]=0;break;
  }
  if(a[i][j]==0) continue;
  if(a[i+1][j]==0)a[i][j+1]=0;
 }
}


int main()
{
 char a[256][20];
 int n;
 cin>>n;
 int i=0;
 for(;i<n;i++)
 {
    scanf("%s",a[i]);
 }
 f(a,n);
 for(i=0;i<n;i++)
 {
    printf("%s\n",a[i]);
 }
}
 

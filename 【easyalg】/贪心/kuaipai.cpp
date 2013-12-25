#include<iostream>
using namespace std;
void swap(int *a,int i,int j)
{
int temp=a[i];
a[i]=a[j];
a[j]=temp;
}
void sort(int a[],int i,int j)
{
if(i>=j)return;
int l=i,r=j-1;
int t=j;
while(l<=r)
{
while(a[l]<a[t]) l++;
while(r>=i&&a[r]>=a[t])r--;
if(l<r)swap(a,l,r);
else break;
}
swap(a,l,t);
sort(a,i,l-1);
sort(a,l+1,j);
}
int main()
{
    int n;
    int a[10];
    while(true){
    cin>>n;
    int i;
    for(i=0;i<n;i++)cin>>a[i];
    sort(a,0,n-1);
    for(i=0;i<n;i++)cout<<a[i]<<" ";
}
}

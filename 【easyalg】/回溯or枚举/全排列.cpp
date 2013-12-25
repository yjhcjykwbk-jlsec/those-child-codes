////quanpaikie
#include <iostream>
using namespace std;
void swap(char *a,int i,int j){int temp=a[i];a[i]=a[j];a[j]=temp;}
void sort(char *a,int l,int r)
{
    int i=0,j;char temp;
    for(i=l+1;i<=r;i++)
    {
        j=i;temp=a[i];
        while(j>l&&temp<a[j-1]) {a[j]=a[j-1];j--;}
        a[j]=temp;
    }
}
        
int next(char *a,int n)
{
    int j=n-1,k;
    while(j>=1&&a[j]<a[j-1])j--;
    if(j==0) return 0;
    for(k=n-1;a[k]<a[j-1];k--);
    swap(a,j-1,k);
    sort(a,j,n-1);
    return 1;
}
char a[6]="abcde";
void soo(char *a,int n,int num)
{
     int k=1,i,j;
     for(i=2;i<=n;i++)k*=i;
     for( i=0;i<=num;i++)
     {
          for(j=0;j<n;j++)cout<<a[j]<<" ";
          cout<<endl;
          if(next(a,n)==0) {cout<<"extra";break;}
     }
}
int main()
{
   soo(a,5,117);
    
    int i;
    cin>>i;
    return 1;
} 

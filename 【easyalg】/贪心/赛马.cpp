#include<iostream>
#include<iomanip>
using namespace std;
void sort(int *c,int n)
{
    int i,j;
    int temp;
    for(i=1;i<n;i++)
    {
       temp=c[i];
       j=i;
       while(j>0&&c[j-1]>temp){c[j]=c[--j];}
       c[j]=temp; 
    }
     
}
int f(int a[],int b[],int n)
{
    sort(a,n);
    sort(b,n); 
    int i=0,j,min,max;bool get;
    int yin=0,shu=0;
    int l=0,left=0,r=n-1,right=n-1;
    for(i=0;i<n;i++)
    {
       if(b[l]<a[left]) 
       {
          right--;
          l++;
          shu++;
       }
       else if(b[l]>a[left]){l++;left++;yin++;}
       else
       {
           if(b[r]>a[right]) {r--;right--;yin++;}
           else {if(b[l]<a[right])shu++;l++;right--;}
       }
    }
     return yin-shu;
}
  int main()
  {
      int n,i;
      int a[1000],b[1000];
      while(cin>>n&&n!=0)
      {    
           for(i=0;i<n;i++)
           {
                    cin>>b[i];
           }
           for(i=0;i<n;i++)
           {
                    cin>>a[i];
           }
           cout<<200*f(a,b,n)<<endl;
      }
      return 1;
  }          

#include<iostream>
using namespace std;
struct heap
{
       int info[10000];
       int size;
       };
void siftup(int p,heap &a)
{
    int temp=a.info[p];
    int parent=(p-1)/2;
    while(p>0&&temp<a.info[parent])
    {
         a.info[p]=a.info[parent];
         p=parent;
         parent=(parent-1)/2;
         }
    a.info[p]=temp;
}
void siftdown(int p,heap &a)
{
     int l=p*2+1;
     int r=p*2+2;
     int temp=a.info[p];
     while(l<a.size)
     {
        if(r<a.size)
        {
           if(a.info[l]>a.info[r]) l=r;
        }
        if(a.info[l]<temp) a.info[p]=a.info[l];
        else break;
        p=l;
    
        l=2*p+1;r=p*2+2;
     }
     a.info[p]=temp;  
}
void insert(heap& a,int n)
{
     a.info[a.size]=n;
     a.size++;
     siftup(a.size-1,a);
}
int get(heap &a)
{
    int temp=a.info[0];
    a.info[0]=a.info[a.size-1];
    a.size--;
    siftdown(0,a);
    return temp;
}
int f(heap &a)
{
    int n=a.size;
    int sum=0,num=0;
    while(a.size>1)
    {
       num=0;
       num+=get(a);
       num+=get(a);
       sum+=num;
       insert(a,num);
      
    }
    return sum;
}
int main()
{
    int i,n,temp;
    cin>>n;
    heap a;
    a.size=0;
    for(i=0;i<n;i++)
    {
        scanf("%d",&temp);
        insert(a,temp);
    }
    int g=f(a);
    printf("%d\n",g);
}

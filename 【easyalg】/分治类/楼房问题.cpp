#include<iostream>
using namespace std;
struct shade
{
       int l;
       int r; 
       int h;
};
shade shade[100000];
int heighta[200000];
int heightb[200000];
int heightc[200000];
int Left[200000];

//归并 b[] c[]得a[] 
void merge(int *a,int *b,int *c,int n)
{
     int i;
     for(i=0;i<=n;i++)
     {
        if(a[i]<b[i])a[i]=b[i];
        if(a[i]<c[i])a[i]=c[i];
        b[i]=0;c[i]=0;
     }
}
//(i,j)区间二分，分别得到b[]或c[]（表示轮廓顶点n和n+1之间楼高度），再归并 
void f(int *a,int *b,int *c,int i,int j,int n)
{
     int k=0;
     if(i==j)  
     {
                while(Left[k]<shade[i].l) k++;
                while(Left[k]<shade[i].r) 
                {
                   //b[k]=shade[i].h;
                   if(a[k]<shade[i].h) a[k]=shade[i].h;
                   k++;
                }
     }
     else 
     {
          int middle=(i+j)/2;
          f(a,b,c,i,middle,n);
          f(a,c,b,middle+1,j,n);
     }
}

//快排，得到所有楼房轮廓边界的顶点的顺序排列
void swap(int *a,int i,int j){int temp=a[i];a[i]=a[j];a[j]=temp;}
void sort(int *a,int i,int j)
{
     if(i>=j)return;
     int middle=(i+j)/2;
     swap(a,middle,j); 
     int left=i,right=j-1;
     while(left<right)
     {
     while(left<=j&&a[left]<a[j]) {left++;}
     while(right>=0&&a[right]>a[j]) {right--;}
     if(left<right) swap(a,left,right);
     }
     if(a[left]>a[j]) swap(a,left,j);
     sort(a,i,left-1);
     sort(a,left+1,j);
} 
     
int main()
{
    int n,i,j;
    cin>>n;
    for(i=0;i<n;i++)
    {
        scanf("%d %d %d",&(shade[i].l),&(shade[i].r),&(shade[i].h));
        Left[2*i]=shade[i].l;Left[2*i+1]=shade[i].r;
    }
    n-=1;
    sort(Left,0,2*n+1);
    f(heighta,heightb,heightc,0,n,2*n+1);
    
    i=0;
    int last=0;
    int left=1;
    while(i<=2*n+1)
    {
       if(heighta[i]>last) printf("U %d\n",heighta[i]-last);
       if(heighta[i]<last) printf("D %d\n",last-heighta[i]);
       if(i==2*n+1) break; 
       last=heighta[i];left=i;
       while(i<2*n+1&&heighta[i]==last) i++;
       if(Left[i]>Left[left])
       {
            printf("R %d\n",Left[i]-Left[left]);    
       }
    }
    return 1;
}
    


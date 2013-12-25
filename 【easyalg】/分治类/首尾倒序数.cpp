#include <iostream>
using namespace std;
int num[50000]; 
//节省空间，同时能快速存储和查阅任意ij之间的最大最小值下标 
int rmq[50000][20]; // rmq[i][j]表示从i开始长为2^j的区段中最小值的位置，j为logn数量级 
int rmp[50000][20]; // rmp[i][j]表示从i开始长为2^j的区段中最大值的位置 
//返回较小值下标 
int Min(int a, int b) 
{ 
    return num[a] < num[b] ? a : b; 
} 
//较大值下标 
int Max(int a, int b) 
{ 
    return num[a] > num[b] ? a : b; 
} 
// 初始化rmq数组 
void InitR(int n) 
{ 
    int i, j; 
    for (i = 0; i < n; i ++) 
    { 
        rmq[i][0] = i; 
        rmp[i][0] = i; 
    } 
    for (i = 1; (1<<i)<=n; i ++) 
    { 
        for (j = 0; j < n; j ++) 
        { 
            rmq[j][i] = rmq[j][i-1];
            rmp[j][i] = rmp[j][i-1]; 
            if (j + (1<<(i-1)) < n) 
            { 
              //num[j]--num[j+2^(i-1)]与num[j+2^(i-1)]--num[j+2^i]相邻两个区间最小值传给 rmq[j][i]
                rmq[j][i] = Min(rmq[j][i], rmq[j+(1<<(i-1))][i-1]); 
                rmp[j][i] = Max(rmp[j][i], rmp[j+(1<<(i-1))][i-1]); 
            } 
        } 
    } 
} 
// 查询下标从f到t的这一段数中(包含f和t)的最小值. 
// 返回最小值的下标 
int QueryMin(int f, int t) 
{ 
    int i; 
    int l = t - f + 1; 
    for (i = 0; (1<<(i+1))<=l; i ++); 
    //num[f]--num[f+2^(i)]与num[t-2^i+1]--num[t]两个相交区间组成整个ft区间，将二者间最小值返回 ，相当于返回整个区间最小值 
    //f+2^(i+1)>t>=f+2^i
    return Min(rmq[f][i], rmq[t-(1<<i)+1][i]); 
} 
// 查询下标从f到t的这一段数中(包含f和t)的最大值. 
// 返回最大值的下标 
int QueryMax(int f, int t) 
{ 
    int i; 
    int l = t - f + 1; 
    for (i = 0; (1<<(i+1))<=l; i ++); 
    return Max(rmp[f][i], rmp[t-(1<<i)+1][i]); 
} 

//-----主调函数 ----分治 
int function(int f,int t)
{
    if(f>=t) return -1;
    int min=QueryMin(f,t);
    int max=QueryMax(f,t);
    int a,b,c; 
    if(min<max)
    {
       a=max-min;
       if(min-1-f>a)
       {
           b=function(f,min-1);
       }
       else b=-1;
       if((t-1-max>a)&&(t-1-max>b))
       {
           c=function(max+1,t);
       }
       else c=-1;
    }
    else if(min>max)
    {
         a=function(max+1,min-1);
         b=function(f,max);
         c=function(min,t);
    }
    if(a<b) a=b;
    if(a<c) a=c;
    return a;
}

int main()
{
    int i,j=0,len,n; 
    while(scanf("%d",&n)!=EOF)
    {
           for (i = 0; i < n; i ++) scanf("%d",&num[i]);
           InitR(n); 
           len = function(0, n-1); 
           printf("%d\n",len);
     }
    return 1;
}

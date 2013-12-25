#include <iostream>
using namespace std;
int num[50000]; 
//��ʡ�ռ䣬ͬʱ�ܿ��ٴ洢�Ͳ�������ij֮��������Сֵ�±� 
int rmq[50000][20]; // rmq[i][j]��ʾ��i��ʼ��Ϊ2^j����������Сֵ��λ�ã�jΪlogn������ 
int rmp[50000][20]; // rmp[i][j]��ʾ��i��ʼ��Ϊ2^j�����������ֵ��λ�� 
//���ؽ�Сֵ�±� 
int Min(int a, int b) 
{ 
    return num[a] < num[b] ? a : b; 
} 
//�ϴ�ֵ�±� 
int Max(int a, int b) 
{ 
    return num[a] > num[b] ? a : b; 
} 
// ��ʼ��rmq���� 
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
              //num[j]--num[j+2^(i-1)]��num[j+2^(i-1)]--num[j+2^i]��������������Сֵ���� rmq[j][i]
                rmq[j][i] = Min(rmq[j][i], rmq[j+(1<<(i-1))][i-1]); 
                rmp[j][i] = Max(rmp[j][i], rmp[j+(1<<(i-1))][i-1]); 
            } 
        } 
    } 
} 
// ��ѯ�±��f��t����һ������(����f��t)����Сֵ. 
// ������Сֵ���±� 
int QueryMin(int f, int t) 
{ 
    int i; 
    int l = t - f + 1; 
    for (i = 0; (1<<(i+1))<=l; i ++); 
    //num[f]--num[f+2^(i)]��num[t-2^i+1]--num[t]�����ཻ�����������ft���䣬�����߼���Сֵ���� ���൱�ڷ�������������Сֵ 
    //f+2^(i+1)>t>=f+2^i
    return Min(rmq[f][i], rmq[t-(1<<i)+1][i]); 
} 
// ��ѯ�±��f��t����һ������(����f��t)�����ֵ. 
// �������ֵ���±� 
int QueryMax(int f, int t) 
{ 
    int i; 
    int l = t - f + 1; 
    for (i = 0; (1<<(i+1))<=l; i ++); 
    return Max(rmp[f][i], rmp[t-(1<<i)+1][i]); 
} 

//-----�������� ----���� 
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

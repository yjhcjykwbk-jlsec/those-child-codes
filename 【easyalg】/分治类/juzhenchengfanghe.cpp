
#include <stdio.h>
typedef int MAT[31][31];
int    n;
int    m;
int    k;
int    d[31][31][31];
unsigned int    di[31];
void print(int e[31][31]);
void    mul(int    a[31][31], int b[31][31],int ans[31][31])
{
    int    i;
    int    j;
    int    s;
    int    c;
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            s = 0;
            for (c=0; c<n; c++)
                s=s+(a[i][c])*(b[c][j]);
            ans[i][j]=s%m;
        }
    }
}
void    add(int a[31][31], int b[31][31], int ans[31][31])    
{
    int    i;
    int    j;
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            ans[i][j]=(a[i][j]+b[i][j])%m;
}
void    mulk(int a[31][31], int kk, int e[31][31])
{
    int    i;
    int    j;
    int    l;
    int tt[31][31];
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            e[i][j] = (i==j)?1:0;
    for (i=30; i>=0&&kk!=0; i--)
    {
        if ( kk >= di[i] )
        {
            kk -= di[i];
            mul(e, d[i], tt);
            int ii;
            int jj;
            for (ii=0; ii<n; ii++)
            for (jj=0; jj<n; jj++)
            e[ii][jj]=tt[ii][jj];
        }
    }
}
void print(int s[31][31])
{
     int         i;
     int         j;
     for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            printf("%d", s[i][j]);
            if (j!=n-1) printf(" ");
            else printf("\n");
        }
    }
}
void f(MAT A, MAT ans, int k1)
{
     int e[31][31];
    int    s1[31][31];
    int    s2[31][31];
    int    t[31][31];
    int    r[31][31];
    MAT* q1;
    MAT* q2;
    MAT* q3;
    int    i;
    int    j;
    int a=k1/2;
    if (a!=0)
    {
       mulk(A,a,t);
       for (i=0; i<n; i++)
           for (j=0; j<n; j++)
                      t[i][j]+=(i==j)?1:0;
       f(A, s1, a);
    }
    else
    {
         for (i=0; i<n; i++)
             for (j=0; j<n; j++)
                 t[i][j] = (i==j)?1:0;
    }
    mul(s1,t,ans);
    if (k1%2!=0)
    {
                   mulk(A,k1,r);
                   add(r,ans,ans);
    }
}
int main()
{
    int i;
    int j;
    MAT A;
    MAT ans;
    scanf("%d%d%d", &n, &k, &m);
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
        {
            scanf("%d", &A[i][j]);
            A[i][j] = A[i][j] % m;
            d[0][i][j] = A[i][j];
        }
    di[0] = 1;
    for (i=1; i<31; i++)
    {
        mul(d[i-1], d[i-1], d[i]);
        di[i] = di[i-1] * 2;
    }
    f(A, ans,k);
    print(ans);
    return 0;
}         

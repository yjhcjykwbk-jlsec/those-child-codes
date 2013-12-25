
#include<iostream>
using namespace std;
int f(int *a,int t[][100][100],int m,int n)
{
int i,j,k,l,s=1;
int num[100];
int able[100];
int match[100][100];
int index=-1;
int max=0;
int q=(1<<n);
int p1=0,q1,r1;
int a1=0,a2=0;

for(i=0;i<q;i++)
{
    j=i;
    l=0;
    a1=a2=0;
    for(k=1;k<=n;k++)
    {
        if(j&1) 
        {
        if(a2==1||a1==1)   {goto f1;}
        }
        a2=a1;
        a1=(j&1);
        l+=a1;
        j>>=1;
    }
    able[++index]=i;
    num[index]=l;
    f1:;
}     
 
for(p1=0;p1<=index;p1++)
{
    for(q1=0;q1<=p1;q1++)
    {
                 if(able[p1]&able[q1]) match[p1][q1]=match[q1][p1]=0;
                 else            match[p1][q1]=match[q1][p1]=1;
    }
}

if(m==0) return 0;
max=0;
if(m==1)
{
    for(p1=0;p1<=index;p1++)
    {
           if(!(a[0]&able[p1]))
           {
                 if(num[p1]>max) max=num[p1];
           }
    }
    return max;
}      

for(l=0;l<m-1;l++)
{
s=1-s;
for(p1=0;p1<=index;p1++)
{
    i=able[p1];
	for(q1=0;q1<=index;q1++)
	{
        j=able[q1];
		if(!(a[l+1]&j)&&match[p1][q1]&&!(a[l]&i))
		{
			if(l==0) 
			{
 	            t[s][p1][q1]=num[p1]+num[q1];
			}
			else 
			{
                 max=0;
                 for(r1=0;r1<=index;r1++)
			     {
			       if(t[1-s][r1][p1]>max)
				   {
					if(match[r1][q1])
						max=t[1-s][r1][p1];
		           }
			     }
			     t[s][p1][q1]=max+num[q1];
            }
		}
		else t[s][p1][q1]=0;
	}
}
}
max=0;
for(i=0;i<=index;i++)
{
for(j=0;j<=index;j++)
	{
		if(max<t[s][i][j]) max=t[s][i][j];
	}
}
return max;
}
int main()
{
    int m,n;
    int t[2][100][100];
    int a[100];
    char s[20];
    scanf("%d %d",&m,&n);
    for(int i=0;i<m;i++)
    {
            scanf("%s",s);
            a[i]=0;
            for(int k=0;k<n;k++)
            {
            a[i]*=2;
            if(s[k]=='H') a[i]+=1;
            }
    }
    printf("%d",f(a,t,m,n));
    return 1;
} 

#include<iostream>
using namespace std;
int ksum(double *a, int s, int e, double k) 
{ 
  int i; 
  double x; 
  for (x = 1.0; x <= k; x += x) { 
    for (i = s; i < e; i++) { 
      if (x == a[i]) { 
        k -= x; 
      } 
    } 
  } 
  for (i = s; i < e; i++) { 
    if (abs((int)((k - a[i]) * 10000)) == 0) { 
      k -= a[i]; 
    } 
  } 
  if (abs((int)(k * 10000)) == 0) { 
    return 1; 
  } 
  else if (k > 0) { 
    return 0; 
  } 
  else if (k < 0 && s < e) { 
    return ksum(a, s, e-1, k-a[e-1]) || 
      ksum(a, s, e-1, k); 
  } else { 
    return 0; 
  } 
} 
int f(double *a,bool *b,int n,double sum)
{
    int i=0,j;
    double ss=sum,temp;
    for(i=0;i<n;i++)
    {
                    int temp=ksum(a,i+1,n,ss);
                    if(temp) {b[i]=false;}
                    else {b[i]=true; ss=ss-a[i];} 
    }
    int p=-1;
    for(i=0;i<n;i++)
    {
       if(b[i]) a[++p]=a[i];
    }
    for(i=0;i<p;i++)
    {
       for(j=p;j>i;j--)
       {
         if(a[j]<a[j-1]) {temp=a[j];a[j]=a[j-1];a[j-1]=temp;}
       }
    }
    return p;
}
int main()
{
    double a[1000];
    bool b[1000];
    int n;
    double sum;
    int temp;
    cin>>n>>sum;
    int i;
    for(i=0;i<n;i++) {cin>>a[i];}
    int p=f(a,b,n,sum);
    for(i=0;i<=p;i++) printf("%g\n",a[i]);
	return 1;
} 
 
 

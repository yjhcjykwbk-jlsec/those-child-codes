#include<iostream>
#include<iomanip>
using namespace std;
struct dev
{
int width;
int price;
};
void sort(dev a[],int n)
{
int i,j;
dev temp;
for(i=1;i<n;i++)
{
   temp=a[i];
   j=i;
   while(j>0&&a[j-1].width<temp.width){a[j]=a[j-1];--j;}
   a[j]=temp; 
}
}

float f(dev a[][100],int num[],int n)
{
int index[100],min[100];
int i,j,k,minp,minwidth,p;
float minbp=0,curbp;
for(p=0;p<n;p++)
{
 for(k=0;k<n;k++) {index[k]=min[k]=0;}
 for(i=0;i<num[p];i++)
 {
   minp=0;
   minwidth=a[p][i].width;
   for(j=0;j<n;j++)
   {
     while(index[j]<num[j]&&a[j][index[j]].width>=minwidth)
     {
     if(a[j][index[j]].price<min[j]||min[j]==0){min[j]=a[j][index[j]].price;}
     index[j]++;
     }
     if(min[j]==0)break;
     minp+=min[j];
   }
   if(j==n)
   {
     curbp=(float)minwidth/minp;
     if(minbp<curbp)
     {
            minbp=curbp;
     }
   }
 }
}
return minbp;
}

int main()
{
int n,cases,Case,i,j,k;
int num[100];
dev a[100][100];
float res;
cin>>cases;
for(Case=0;Case<cases;Case++){
cin>>n;
for(i=0;i<n;i++)
{
cin>>num[i];
for(k=0;k<num[i];k++)
{
cin>>a[i][k].width>>a[i][k].price;
}
sort(a[i],num[i]);
}
res=f(a,num,n);

printf("%.3f\n",res);
}
return 1;
}
